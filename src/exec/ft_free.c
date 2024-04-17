/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:38:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 11:24:47 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	close_fderror(t_redir *redir)
{
	t_redir	*ptr;

	ptr = redir;
	while (ptr != NULL && ptr->fd > 2)
	{
		close(ptr->fd);
		ptr = ptr->next;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*ptr;

	ptr = redir;
	while (ptr != NULL)
	{
		if (ptr->path != NULL)
			free(ptr->path);
		ptr = ptr->next;
	}
}

void	ft_free_cmd_structure(t_cmd *cmd_structure)
{
	t_cmd	*temp;

	close_allfd(cmd_structure);
	end_pipes(cmd_structure);
	if (!cmd_structure)
		return ;
	while (cmd_structure)
	{
		temp = cmd_structure->next;
		if (cmd_structure->path != NULL)
			free(cmd_structure->path);
		if (cmd_structure->args != NULL)
			ft_free_double_pointers(cmd_structure->args);
		if (cmd_structure->redir != NULL)
		{
			ft_free_redir_list(cmd_structure->redir);
			cmd_structure->redir = NULL;
		}
		if (cmd_structure != NULL)
			free(cmd_structure);
		cmd_structure = temp;
	}
}

void	ft_free_redir_list(t_redir *redir)
{
	t_redir	*temp;

	while (redir != NULL)
	{
		temp = redir;
		if (temp->path != NULL)
		{
			free(temp->path);
			temp->path = NULL;
		}
		redir = redir->next;
		free(temp);
	}
}
