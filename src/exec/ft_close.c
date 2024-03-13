/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:50:56 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/07 16:50:58 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void ft_close(t_cmd **commands)
{
    t_cmd *ptr;

    t_redir *redirptr;

    ptr = (*commands);

    while(ptr != NULL)
    {
        redirptr = ptr->redir;
        while(redirptr != NULL)
        {
            close(redirptr->fd);
            redirptr = redirptr->next;
        }
        close(ptr->pipesfd[0]);
        close(ptr->pipesfd[1]);
        ptr = ptr->next;
    }
    ptr = (*commands);

}