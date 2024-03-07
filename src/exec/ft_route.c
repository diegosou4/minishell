/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/07 12:27:15 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int ft_countpipes(t_cmd *cmd)
{
    int i;
    i = 0;
    t_cmd *ptr;

    ptr = cmd;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);
}


void open_pipes(t_cmd **cmd)
{
    t_cmd *ptr;
    ptr = (*cmd);
    while(ptr != NULL)
    {
        pipe(ptr->pipesfd);
        ptr = ptr->next;
    }
}

void executor_without(t_cmd *commands, char **env, int in,int out)
{
    int pid;

    pid = fork();
    if(pid == 0)
    {
        dup2(in, 0);
        dup2(out,1);
        if(in != 0)
            close(in);
        if(out != 1)
            close(out);
        execve(commands->path,commands->args,env);
    }
    if(out != 1)
        close(out);
    if(in != 0)
        close(in);
}



void ft_magane_executor(t_cmd **cmd, char **env) 
{
    t_cmd *ptr;
    t_cmd *prev;
 
    ptr = (*cmd);
    executor_without(ptr, env, 0, ptr->pipesfd[1]);
    prev = (*cmd);
    ptr = ptr->next;
    while(ptr->next != NULL)
    {
        executor_without(ptr, env, prev->pipesfd[0], ptr->pipesfd[1]);
        prev = ptr;
        ptr = ptr->next;
    }
    executor_without(ptr, env, prev->pipesfd[0], 1);
}




