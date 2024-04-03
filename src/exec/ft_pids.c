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
    int prev_exit;
    int error_flag;

    error_flag = 0;
    prev_exit = 0;
    j = 0;

    while(j != sizepipe(bash_boss->commands))
    {
        waitpid(bash_boss->pid[j],&bash_boss->exit_status,0);
        if (bash_boss->exit_status == 256)
            prev_exit =  bash_boss->exit_status - 129;
        else if (bash_boss->exit_status == 2)
            prev_exit = 130;
        else if (bash_boss->exit_status == 3)
            prev_exit = 131;
        else
            prev_exit = (bash_boss->exit_status & 0xff00) >> 8;
        if (prev_exit != 0)
        {
            error_flag = 1;
            g_exit_status = prev_exit;
        }
        j++;
    }
    if (!error_flag)
        g_exit_status = 0;
}