/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:43:09 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/07 00:18:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	care_redirect(t_cmd **cmd, t_bash **bash_boss)
{
	(*bash_boss)->fdout = return_out((*cmd));
	(*bash_boss)->fdin = return_in((*cmd));
	if ((*cmd)->prev != NULL)
		close_myhereprev((*cmd)->prev);
	if ((*cmd) != NULL)
		close_myherenext((*cmd)->next);
	if ((*cmd)->executable == 0)
	{
		printf("Preciso da free");
		exit(EXIT_FAILURE);
	}
}

void	care_expand(t_cmd **cmd, t_bash **bash_boss)
{
	if (expand_path_cpy(cmd, (*bash_boss)->cpyenv) == 1)
	{
		fail_expander((*bash_boss), (*cmd));
		g_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	dup_final(t_bash *bash_boss, t_cmd *cmd)
{
	if(cmd->args[0] == NULL)
	{
		if(bash_boss->fdin != - 1)
			close(bash_boss->fdin);
		if(bash_boss->fdout != - 1)
			close(bash_boss->fdout);
		ft_exit(bash_boss->commands);	
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

	signal(SIGINT, SIG_IGN);
	ptr = bash_boss->commands;
	get_file_num()->exit_code = 0;
	while (ptr != NULL)
	{
		check_heredoc(&ptr->redir, ptr,bash_boss);
		if (get_file_num()->exit_code == 127)
			break ;
		ptr = ptr->next;
	}
	if (get_file_num()->exit_code == 127)
	{
		return ;
	}
	ptr = bash_boss->commands;
	bash_boss->pipein = -1;
	bash_boss->pipeout = -1;
	while (ptr != NULL)
	{
		ptr->executable = 1;
		ptr = ptr->next;
	}
	ft_magane_executor(bash_boss);
	ft_signal_manager();
}
