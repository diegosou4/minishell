/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:38:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:46:45 by diegmore         ###   ########.fr       */
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
