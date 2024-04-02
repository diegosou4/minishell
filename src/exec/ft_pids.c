/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pids.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:30:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 19:11:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void alloc_mypids(t_bash *bash_boss)
{
    int pipes;
    pipes = ft_howpipes(bash_boss->commands);
    bash_boss->pid = ft_calloc(sizeof(int) , pipes);
}

void wait_mypids(t_bash *bash_boss)
{   
    int j;
    j = 0;
    while(j != sizepipe(bash_boss->commands))
    {
        waitpid(bash_boss->pid[j],&bash_boss->exit_status,0);
        j++;
    }
    g_exit_status = (bash_boss->exit_status & 0xff00) >> 8;
}