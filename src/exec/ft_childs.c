/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:01:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/13 12:31:21 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	return_in(t_bash *bash_boss,t_redir *ptr)
{
	if(ptr->token == redir_out || ptr->token == append_out)
	{
		if (bash_boss->fdout != -1)
			close(bash_boss->fdout);
		if(ptr->token == redir_out)
			bash_boss->fdout = open_out(ptr->path);
		else
			bash_boss->fdout = open_append(ptr->path);
		if(bash_boss->fdout < 0)
				return(-1);
	}
	return(EXIT_SUCCESS);
}


int	return_out(t_bash *bash_boss,t_redir *ptr)
{
	if(ptr->token == redir_in || ptr->token == open_here)
	{	
		if (bash_boss->fdin != -1)
			close(bash_boss->fdin);
		if (ptr->token == redir_in)
			bash_boss->fdin = open_in(ptr->path);
		if (ptr->token == open_here)
			bash_boss->fdin = ptr->fd;
		if (bash_boss->fdin < 0)
				return (-1);
	}
	return (EXIT_SUCCESS);
}

int return_intout(t_cmd *cmd,t_bash *bash_boss)
{
	t_redir *ptr;

	ptr = cmd->redir;
	bash_boss->fdin = -1;
	bash_boss->fdout = -1;
	while(ptr != NULL)
	{
		if(return_in(bash_boss,ptr) == -1 || return_out(bash_boss,ptr))
		{
			cmd->executable = 0;
			return(-1);
		}
		ptr = ptr->next;
	}
	return(1);
}


void only_redir(t_cmd *current, t_bash *bash_boss)
{
	t_redir *ptr;

	ptr = current->redir;


	if(current->args[0] == NULL)
	{
		if(current->pipes[0] != -1)
			close(current->pipes[0]);
		if(current->pipes[1] != -1)
			close(current->pipes[1]);
		close_error(bash_boss);
		free_here(bash_boss);
		free_pids(bash_boss);
		exit(EXIT_SUCCESS);
	}
}


void	child_exec(t_cmd *cmd, t_bash *bash_boss)
{
	char **new;

	
	only_redir(cmd,bash_boss);
	care_expand(&cmd, &bash_boss);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss,cmd);
	new = newenv_child(bash_boss->cpyenv);
	check_dir(bash_boss,cmd,new);
	execve(cmd->path, cmd->args, new);
}


void	child_build(t_cmd *cmd, t_bash *bash_boss)
{
	int	check;
	check = check_builtings(cmd);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss,cmd);
	execute_builtings(&cmd, &bash_boss->cpyenv, check);
	free_here(bash_boss);
	free_pids(bash_boss);
	exit(EXIT_SUCCESS);
}


void	care_myprev(t_cmd *ptrcmd)
{
	if (ptrcmd->prev)
	{
		close(ptrcmd->prev->pipes[0]);
		close(ptrcmd->prev->pipes[1]);
	}
}
void	pipes_executor(t_cmd *ptrcmd, t_bash *bash_boss)
{
	int		i;
	t_cmd	*ptr;
	i = 0;

	ptr = ptrcmd;
	alloc_mypids(bash_boss);
	while (ptrcmd != NULL)
	{
		set_pipes(ptrcmd);
		bash_boss->pid[i] = fork();
		if (bash_boss->pid[i] == 0)
		{
			check_here(bash_boss,ptrcmd);
			care_redirect(&ptrcmd, &bash_boss);
			if (check_builtings(ptrcmd) == 0)
				child_exec(ptrcmd, bash_boss);
			else
				child_build(ptrcmd, bash_boss);
		}
		care_myprev(ptrcmd);
		ptrcmd = ptrcmd->next;
		i++;
	}
	wait_mypids(bash_boss);
	free_pids(bash_boss);
}

