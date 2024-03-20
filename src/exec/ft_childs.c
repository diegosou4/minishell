/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:01:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 17:01:13 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"



void simple_execution(t_bash *bash_boss,t_cmd *ptrcmd,t_bash *executor)
{
    int pid;
    init_mybash(bash_boss,ptrcmd,executor);
    if(check_builtings(ptrcmd) > 0)
    {
        child_builtings(&ptrcmd,&bash_boss->cpyenv);
        return;
    }
    pid = fork();
    if(pid == 0)
    {
        child_executor(executor,ptrcmd,bash_boss);
    }
    int i =0;
    waitpid(pid,&i,0);
    //printf("status: %d\n", WEXITSTATUS(i));



}




void many_execution(t_bash *bash_boss, t_cmd *ptrcmd,t_bash *executor)
{
    int i;
    i = 0;
    
    while(ptrcmd != NULL)
    {
        init_mybash(bash_boss,ptrcmd,executor);
        pid = fork();
        if(pid == 0)
        {
            if(check_builtings(ptrcmd) == 0)
              //  child_executor(executor);
            else
                child_bexecutor(executor);  
                close(executor->in);
                close(executor->out);        
        }
        executor->last = ptrcmd;
        closeoutpipe(&executor->last);
        ptrcmd = ptrcmd->next;
      
    }  */
}



