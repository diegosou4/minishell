/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:14:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 16:00:04 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	manage_heredoc(t_bash **bash_boss)
{
	t_cmd	*ptr;

	ptr = (*bash_boss)->commands;
	signal(SIGINT, SIG_IGN);
	get_file_num()->exit_code = 0;
	get_file_num()->heredoc = 1;
	while (ptr != NULL)
	{
		ft_signal_manager_child();
		check_heredoc(&ptr->redir, ptr, (*bash_boss));
		if (get_file_num()->exit_code == 127)
			break ;
		ptr = ptr->next;
	}
}

void	check_heredoc(t_redir **redirect, t_cmd *cmd, t_bash *bash_boss)
{
	t_redir	*ptr;

	ptr = (*redirect);
	while (ptr != NULL)
	{
		if (ptr->token == here_doc)
		{
			ptr->fd = ft_heredoc(ptr->path, bash_boss, cmd);
			if (len_darray(cmd->args) == 0)
				close(ptr->fd);
			if (get_file_num()->exit_code == 127)
				return ;
			ptr->token = open_here;
		}
		ptr = ptr->next;
	}
}

void	close_myhere(t_cmd *cmd)
{
	t_cmd	*ptr;
	t_redir	*ptrredir;

	ptr = cmd;
	while (ptr != NULL)
	{
		ptrredir = cmd->redir;
		while (ptrredir != NULL)
		{
			if (ptrredir->token == open_here)
			{
				if (ptrredir->fd > 0)
					close(ptrredir->fd);
			}
			ptrredir = ptrredir->next;
		}
		ptr = ptr->next;
	}
}

void	close_myhereprev(t_cmd *cmd)
{
	t_cmd	*ptr;
	t_redir	*ptrredir;

	ptr = cmd;
	while (ptr != NULL)
	{
		ptrredir = ptr->redir;
		while (ptrredir != NULL)
		{
			if (ptrredir->token == open_here)
			{
				if (ptrredir->fd != -1)
					close(ptrredir->fd);
			}
			ptrredir = ptrredir->next;
		}
		ptr = ptr->prev;
	}
}

void	check_here(t_bash *bash_boss, t_cmd *cmd)
{
	if (get_file_num()->heredoc == 0)
	{
		if (bash_boss->fdin != -1)
			close(bash_boss->fdin);
		if (bash_boss->fdout != -1)
			close(bash_boss->fdout);
		if (cmd->pipes[0] != -1)
			close(cmd->pipes[0]);
		if (cmd->pipes[1] != -1)
			close(cmd->pipes[1]);
		free_here((bash_boss));
		free_pids((bash_boss));
		exit(EXIT_FAILURE);
	}
}
