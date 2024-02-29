/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:28:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/26 13:28:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"
/*
void execute_cmd(t_cmd *commands, char **env)
{
    t_redir *ptr;
    int in;
    int out;
    in = 0;
    out = 1;
    int fd[2];

    pipe(fd);
    openredir(commands->redir);
    ptr = commands->redir;
    if(ptr != NULL)
    {
    while(ptr->next)
    {
        if(ptr->token == 2)
        {
            if(in != 1)
                close(in);
            else
                in = dup(ptr->fd);
        }
        ptr = ptr->next;
    }
    }
 

}

void exec_simple(t_cmd *commands,char **env)
{
    int pid;
    pid = fork();
    if(pid == 0)
    {
    execve(commands->path,commands->args,env);
    }
    wait(NULL);
}   */


void execution(t_cmd *commands, t_env **env)
{
    t_cmd *ptr;
    int build;
    ptr = commands;
    if(sizepipe(commands) == 1)
    {
        build = check_builtings(commands);
        if(build == 1)
            print_pwd(); 
        else if(build  == 2)
            ft_cd(commands,env);
        else if(build == 3)
            execute_env(*env,commands);       
    }
}



int sizeredir(t_redir *redir)
{
    int i;
    i = 0;

    t_redir *ptr;
    
    ptr = redir;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);

}


int sizepipe(t_cmd *commands)
{
    int i;
    i = 0;

    t_cmd *ptr;

    ptr = commands;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);
}