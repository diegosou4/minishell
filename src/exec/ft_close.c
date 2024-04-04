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