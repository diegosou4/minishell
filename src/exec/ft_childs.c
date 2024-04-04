/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:01:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:50:02 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	return_in(t_cmd *cmd)
{
	t_redir	*ptr;
	int		fd;

	fd = -1;
	ptr = cmd->redir;
	while (ptr != NULL)
	{
		if (ptr->token == redir_in || ptr->token == open_here)
		{
			if (fd != -1)
				close(fd);
			if (ptr->token == redir_in)
				fd = open_in(ptr->path);
			if (ptr->token == open_here)
				fd = ptr->fd;
			if (fd < 0)
			{
				cmd->executable = 0;
				return (fd);
			}
		}
		ptr = ptr->next;
	}
	return (fd);
}

int	return_out(t_cmd *cmd)
{
	t_redir	*ptr;
	int		fd;

	fd = -1;
	ptr = cmd->redir;
	while (ptr != NULL)
	{
		if (ptr->token == redir_out || ptr->token == append_out)
		{
			if (fd != -1)
				close(fd);
			if (ptr->token == redir_out)
				fd = open_out(ptr->path);
			else
				fd = open_append(ptr->path);
			if (fd < 0)
			{
				cmd->executable = 0;
				return (fd);
			}
		}
		ptr = ptr->next;
	}
	return (fd);
}

void	child_exec(t_cmd *cmd, t_bash *bash_boss)
{
	care_redirect(&cmd, &bash_boss);
	care_expand(&cmd, &bash_boss);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss,cmd);
	execve(cmd->path, cmd->args, bash_boss->env);
}

void	child_build(t_cmd *cmd, t_bash *bash_boss)
{
	int	check;

	check = check_builtings(cmd);
	care_redirect(&cmd, &bash_boss);
	care_expand(&cmd, &bash_boss);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss,cmd);
	execute_builtings(&cmd, &bash_boss->cpyenv, check);
	freedouble_malloc(bash_boss->env,len_darray(bash_boss->env));
	free_cpyenv(bash_boss->cpyenv);
	free_all(cmd);
	if (bash_boss->pid != NULL)
	 	free(bash_boss->pid);
	exit(EXIT_SUCCESS);
}

void	pipes_executor(t_cmd *ptrcmd, t_bash *bash_boss)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = ptrcmd;
	alloc_mypids(bash_boss);
	ft_signal_manager_child();
	while (ptrcmd != NULL)
	{
		set_pipes(ptrcmd);
		bash_boss->pid[i] = fork();
		if (bash_boss->pid[i] == 0)
		{
			if (check_builtings(ptrcmd) == 0)
				child_exec(ptrcmd, bash_boss);
			child_build(ptrcmd, bash_boss);
		}
		care_myprev(ptrcmd);
		close_myhere(ptrcmd);
		ptrcmd = ptrcmd->next;
		i++;
	}
	wait_mypids(bash_boss);
	close_pipes(bash_boss->commands);
}
