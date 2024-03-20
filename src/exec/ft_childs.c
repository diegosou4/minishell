/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:01:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 19:40:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void simple_execution(t_bash *bash_boss,t_cmd *ptrcmd,t_bash *executor)
{
    int i;
    i = 0;
    alloc_mypids(bash_boss);
    init_mybash(bash_boss,ptrcmd,executor);
    if(check_builtings(ptrcmd) > 0)
    {
        child_builtings(&ptrcmd,&bash_boss->cpyenv);
        return;
    }
    bash_boss->pid[0] = fork();
    if(bash_boss->pid[0] == 0)
        child_executor(executor,ptrcmd,bash_boss);
    waitpid(bash_boss->pid[0],&i,0);
}

void many_execution(t_bash *bash_boss, t_cmd *ptrcmd,t_bash *executor)
{
    int i;
    i = 0;
    alloc_mypids(bash_boss);
    while(ptrcmd != NULL)
    {
        init_mybash(bash_boss,ptrcmd,executor);
        bash_boss->pid[i] = fork();
        if(bash_boss->pid[i] == 0)
        {
            if(check_builtings(ptrcmd) == 0)
               child_executor(executor,ptrcmd,bash_boss);
            else
                child_bexecutor(executor,ptrcmd,bash_boss);
        }
        executor->last = ptrcmd;
        closeoutpipe(&executor->last);
        ptrcmd = ptrcmd->next;
        waitpid(bash_boss->pid[i],&i,0);
        i++;
    }  
}



