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

void executor_without(t_cmd *commands, char **env, int in,int out,t_env **cpy)
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
        if(check_builtings(commands) == 0)
            execve(commands->path,commands->args,env);
        else
            execution(commands,cpy);
        exit(EXIT_SUCCESS);
    }
    if(out != 1)
        close(out);
    if(in != 0)
        close(in);
}


int check_out(t_redir *redir)
{
    int indexout;
    indexout = 0;
    int fd;
    t_redir *ptr;

    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 1)
            indexout++;
        ptr = ptr->next;
    }
    return(indexout);
}




void ft_magane_executor(t_cmd **cmd, char **env,t_env **cpy)
{
    t_cmd *ptr;
    t_cmd *prev;
    int index;
    index = 0;
    ptr = (*cmd);
    if(ptr->redir != NULL)
        index = check_out(ptr->redir);
    if(index != 0)
    {
        t_redir *ptrredir;
        ptrredir = (*cmd)->redir;
        int i;
        i = 0;
        while(i < index - 1)
        {
            ptrredir = ptrredir->next;
            i++;
        }
         executor_without(ptr, env, 0, ptrredir->fd,cpy); 
    }
    /*
    prev = (*cmd);
    ptr = ptr->next;ft_close
        executor_without(ptr, env, prev->pipesfd[0], ptr->pipesfd[1],cpy);
        prev = ptr;
        ptr = ptr->next;
    }
    executor_without(ptr, env, prev->pipesfd[0], 1,cpy);
    */
}
/*
void case_redir(t_redir *redir)
{
  
}*/

int case_redi(int token, char *path)
{
    int fd;

    if(token == 1)
        fd = open(path,O_WRONLY | O_CREAT | O_TRUNC, 0664);
    else if(token == 2)
    {
        fd = open(path,O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(access(path,R_OK) == 0)
            return(fd);
        else
        {
            perror("Error");
            return(-1);
        }
    }
        
    return(fd);
}

void start_exection(t_cmd **commands,char **env,t_env **cpy)
{
    t_cmd *ptr;
    ptr = (*commands);
    t_redir *redptr;
    while(ptr != NULL)
    {
        redptr = ptr->redir;
        while(redptr != NULL)
        {
            redptr->fd = case_redi(redptr->token,redptr->path);
            redptr = redptr->next;
        }
        ptr = ptr->next;
    }
    ft_magane_executor(commands,env,cpy);
    ft_close(commands);
}