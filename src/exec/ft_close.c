/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:50:56 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/04 21:56:12 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


void close_pipes(t_cmd *commands)
{
    t_cmd *ptr;

    ptr = commands;

    while(ptr != NULL)
    {
        if(ptr->pipes[0] > 0)
            close(ptr->pipes[0]);
        if(ptr->pipes[1] > 0)
            close(ptr->pipes[1]);
        ptr = ptr->next;
    }
}

void close_error(t_bash *bash_boss)
{
    if(bash_boss->in != -1)
        close(bash_boss->in);
    if(bash_boss->out != -1)
        close(bash_boss->in);
    if(bash_boss->fdin != - 1)
		close(bash_boss->fdin);
	if(bash_boss->fdout != - 1)
		close(bash_boss->fdout);
	if(bash_boss->pipein != -1)
		close(bash_boss->pipein);
	if(bash_boss->pipeout != -1)
		close(bash_boss->pipeout);

}

void pipes_prev(t_cmd *ptrcmd)
{
    if(ptrcmd->prev != NULL)
	{
		if(ptrcmd->prev->prev != NULL)
		    close(ptrcmd->prev->prev->pipes[0]);
	}
}