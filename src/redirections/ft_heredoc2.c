/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:14:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/07 22:03:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

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
				close(ptrredir->fd);
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
				close(ptrredir->fd);
			ptrredir = ptrredir->next;
		}
		ptr = ptr->prev;
	}
}

void	close_myherenext(t_cmd *cmd)
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
				close(ptrredir->fd);
			ptrredir = ptrredir->next;
		}
		ptr = ptr->next;
	}
}

void check_here(t_bash *bash_boss)
{
	if(get_file_num()->heredoc == 0)
	{
		if(bash_boss->fdin != - 1)
			close(bash_boss->fdin);
		if(bash_boss->fdout != - 1)
			close(bash_boss->fdout);
		free_here((bash_boss));
		free_pids((bash_boss));
		exit(EXIT_FAILURE);
	}
}