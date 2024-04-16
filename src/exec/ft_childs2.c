/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:43:09 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/10 11:58:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	care_redirect(t_cmd **cmd, t_bash **bash_boss)
{
	return_intout((*cmd), (*bash_boss));
	if ((*cmd)->executable == 0)
	{
		if ((*cmd)->pipes[0] != -1)
			close((*cmd)->pipes[0]);
		if ((*cmd)->pipes[1] != -1)
			close((*cmd)->pipes[1]);
		close_error((*bash_boss));
		free_here((*bash_boss));
		free_pids((*bash_boss));
		exit(EXIT_FAILURE);
	}
}

void	care_expand(t_cmd **cmd, t_bash **bash_boss)
{
	if (expand_path_cpy(cmd, (*bash_boss)->cpyenv) == 1)
	{
		care_inchild((*cmd), (*bash_boss));
		fail_expander((*bash_boss), (*cmd));
	}
}

void	dup_final(t_bash *bash_boss, t_cmd *cmd)
{
	if (cmd->args[0] == NULL)
	{
		close_error(bash_boss);
		free_pids(bash_boss);
		free_here(bash_boss);
		exit(EXIT_SUCCESS);
	}
	if (bash_boss->fdin != -1)
	{
		dup2(bash_boss->fdin, STDIN_FILENO);
		close(bash_boss->fdin);
	}
	if (bash_boss->fdout != -1)
	{
		dup2(bash_boss->fdout, STDOUT_FILENO);
		close(bash_boss->fdout);
	}
}

void	start_execution(t_bash *bash_boss)
{
	t_cmd	*ptr;

	ptr = bash_boss->commands;
	manage_heredoc(&bash_boss);
	if (get_file_num()->exit_code == 127)
		return ;
	bash_boss->pipein = -1;
	bash_boss->pipeout = -1;
	while (ptr != NULL)
	{
		ptr->executable = 1;
		ptr = ptr->next;
	}

	ft_magane_executor(bash_boss);
}
