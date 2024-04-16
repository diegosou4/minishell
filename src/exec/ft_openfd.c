/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 10:56:21 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	open_out(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
	{
		printf_error_fd(strerror(errno), path);
		return (fd);
	}
	return (fd);
}

int	open_in(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf_error_fd(strerror(errno), path);
		return (fd);
	}
	return (fd);
}

int	open_append(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd < 0)
	{
		printf_error_fd(strerror(errno), path);
		return (fd);
	}
	return (fd);
}

void	close_allfd(t_cmd *cmd)
{
	t_cmd	*ptrcmd;
	t_redir	*ptr;

	ptrcmd = cmd;
	while (ptrcmd != NULL)
	{
		ptr = ptrcmd->redir;
		while (ptr != NULL)
		{
			if (ptr->fd > 0)
				close(ptr->fd);
			ptr = ptr->next;
		}
		ptrcmd = ptrcmd->next;
	}
}
