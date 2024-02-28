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
}   
void execute_simple(t_cmd *commands, char **env)
{
    if(sizeredir(commands->redir) == 0)
    {
      //  check_builtings(commands);
        exec_simple(commands,env);
        free_commands(commands);
    }
}

void execution(t_cmd *commands, char ***env)
{
    t_cmd *ptr;
    int build;
    ptr = commands;
    if(sizepipe(commands) == 1)
    {
    if(check_builtings(commands,*env) == 1)
        print_pwd(); 
    else if(check_builtings(commands,*env) == 2)
        ft_cd(commands);
    else if(check_builtings(commands,*env) == 3)
        execute_env(*env,commands);    
    else if(check_builtings(commands,*env) == 4)
        ft_export(env,commands);
    else if(check_builtings(commands,*env) == 5)
        ft_unset(env,commands);
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