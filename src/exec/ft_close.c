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