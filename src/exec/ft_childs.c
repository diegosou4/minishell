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





void child_exec(t_cmd *cmd, t_bash *bash_boss)
{

    bash_boss->fdin = -1;
    bash_boss->fdout = -1;
    if(expand_path(&cmd,bash_boss->env) == 1)
        exit(EXIT_FAILURE);
    
    care_inchild(cmd,bash_boss);
    if(bash_boss->fdin != -1) 
    {
        dup2(bash_boss->fdin, STDIN_FILENO);
        close(bash_boss->fdin);
    }
    if(bash_boss->fdout != -1)
    {
         dup2(bash_boss->fdout, STDOUT_FILENO);
        close(bash_boss->fdout);
    } 
    execve(cmd->path,cmd->args,bash_boss->env);
}


void pipes_executor(t_cmd *ptrcmd,t_bash *bash_boss)
{

    int i;
    i = 0;
    t_cmd *ptr;
    ptr = ptrcmd;
    alloc_mypids(bash_boss);
    while(ptrcmd != NULL)
    { 
        set_pipes(ptrcmd);
        bash_boss->pid[i] = fork();
        if(bash_boss->pid[i] == 0)
        { 
           child_exec(ptrcmd,bash_boss); 
        }
        care_myprev(ptrcmd);
        ptrcmd = ptrcmd->next;
        i++;
    }
     wait_mypids(bash_boss);     
}

