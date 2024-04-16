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

int	return_in(t_bash *bash_boss, t_redir *ptr)
{
	if (ptr->token == redir_out || ptr->token == append_out)
	{
		if (bash_boss->fdout != -1)
			close(bash_boss->fdout);
		if (ptr->token == redir_out)
			bash_boss->fdout = open_out(ptr->path);
		else
			bash_boss->fdout = open_append(ptr->path);
		if (bash_boss->fdout < 0)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

int	return_out(t_bash *bash_boss, t_redir *ptr)
{
	if (ptr->token == redir_in || ptr->token == open_here)
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

int	return_intout(t_cmd *cmd, t_bash *bash_boss)
{
	t_redir	*ptr;

	ptr = cmd->redir;
	bash_boss->fdin = -1;
	bash_boss->fdout = -1;
	while (ptr != NULL)
	{
		if (return_in(bash_boss, ptr) == -1 || return_out(bash_boss, ptr) == -1)
		{
			g_exit_status = 1;
			cmd->executable = 0;
			return (-1);
		}
		ptr = ptr->next;
	}
	return (1);
}

void	child_exec(t_cmd *cmd, t_bash *bash_boss)
{
	char	**new;

	only_redir(cmd, bash_boss);
	care_expand(&cmd, &bash_boss);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss, cmd);
	new = newenv_child(bash_boss->cpyenv);
	check_dir(bash_boss, cmd, new);
	if (access(cmd->path, X_OK) == -1)
		ft_notpermission(bash_boss, new);
	else
		execve(cmd->path, cmd->args, new);
	exit_error(bash_boss, new, EXIT_FAILURE);
}

void	child_build(t_cmd *cmd, t_bash *bash_boss)
{
	int	check;

	check = check_builtings(cmd);
	if (sizepipe(bash_boss->commands) != 1)
		care_inchild(cmd, bash_boss);
	redir_inchild(bash_boss);
	dup_final(bash_boss, cmd);
	execute_builtings(&cmd, &bash_boss->cpyenv, check);
	free_here(bash_boss);
	free_pids(bash_boss);
	exit(EXIT_SUCCESS);
}
