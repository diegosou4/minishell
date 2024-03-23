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


void close_child(t_cmd **ptrcmd,t_bash *bash_boss,t_cmd **last)
{
    t_cmd *ptr;
    ptr = (*ptrcmd);
    while(ptr != NULL)
    {
        if(bash_boss->in != ptr->pipesfd[0])
             close(ptr->pipesfd[0]);
        if(bash_boss->out != ptr->pipesfd[1])
            close(ptr->pipesfd[1]);
        ptr = ptr->next;
    }
    if((*last) != NULL)
    {
        if(bash_boss->in != (*last)->pipesfd[0])
            close((*last)->pipesfd[0]);
        if(bash_boss->out != (*last)->pipesfd[1])
            close((*last)->pipesfd[1]);
    }
}