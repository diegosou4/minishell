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
    if(ptr->next != NULL)
    {
        while(ptr != NULL)
        {
            pipe(ptr->pipesfd);
            ptr = ptr->next;
        }
    }
}

void close_pipes(t_cmd **cmd)
{
    t_cmd *ptr;

    ptr = (*cmd);
    if(ptr->next != NULL)
    {
        close(ptr->pipesfd[0]);
        close(ptr->pipesfd[1]);
        ptr = ptr->next;
    }

}

int return_heredoc(t_redir *redir)
{
    int i;
    t_redir *ptr;
    i = 0;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 3)
            return(1);
        ptr = ptr->next;
    }
    return(0);
}
int return_out(t_redir *redir, t_cmd *curr)
{
    int fd;
    t_redir *ptr;
 
    ptr = redir;
    if(curr->next == NULL)
        fd = STDOUT_FILENO;
    else
        fd = curr->pipesfd[1];
    while(ptr != NULL)
    {
        if(ptr->token == 1 || ptr->token == 4 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;
    }
    return(fd);
}

int return_in(t_redir *redir, t_cmd *curr,t_cmd *last)
{
    int fd;
    t_redir *ptr;
    
    if(last == NULL)
        fd = STDIN_FILENO;
    else
        fd = last->pipesfd[0];
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 2 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;        
    }
    return(fd);
}

void child_executor(t_cmd *curr,char **env,t_env **cpy,t_cmd *last)
{

    int fdin;
    int fdout;
 
    fdin = return_in(curr->redir,curr,last);
    fdout = return_out(curr->redir,curr);
   
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
         close(fdout);
    if(fdin != 0)
        close(fdin);
    execve(curr->path,curr->args,env);
}
void child_bexecutor(t_cmd *curr,char **env,t_env **cpy,t_cmd *last)
{
    int check;
    int fdin;
    int fdout;
    check = check_builtings(curr);
    fdin = return_in(curr->redir,curr,last);
    fdout = return_out(curr->redir,curr);
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
        close(fdout);
    if(fdin != 0)
        close(fdin);  
    execute_builtings(&curr,cpy,check);
   
    close(fdin);

    close(fdout);
    exit(0);
}

// Bora trabalhar filho da ***

void closeoutpipe(t_cmd **ptr)
{
    close((*ptr)->pipesfd[1]);
}

void ft_magane_executor(t_cmd **cmd, char **env,t_env **cpy)
{
    int pid;
    t_cmd *ptrcmd;
    t_cmd *lastcmd;
    ptrcmd = (*cmd);
    lastcmd = NULL;
    open_pipes(cmd);
     
    if(ptrcmd->next == NULL)
    {
        child_builtings(&ptrcmd,cpy);
        return;
    }
    while(ptrcmd != NULL)
    {
        pid = fork();
        if(pid == 0)
        {
            if(check_builtings(ptrcmd) == 0)
                child_executor(ptrcmd,env,cpy,lastcmd);
            else
                child_bexecutor(ptrcmd,env,cpy,lastcmd); 
            wait(NULL);
        }
        lastcmd = ptrcmd;
        closeoutpipe(&lastcmd);
        ptrcmd = ptrcmd->next;
    }

    close_pipes(cmd);
}




// Debito de Progamacao
// Voltar e tratar erros de abertura de arquivos

int redir_error(int fd)
{
    if(fd < 0)
        perror("Error ");
    return(0);
}

int open_fd(t_redir **redirect)
{
    t_redir *ptrredir;

    ptrredir = (*redirect);
    while(ptrredir != NULL)
    {
        if(ptrredir->token == 1)
            ptrredir->fd = open(ptrredir->path,O_WRONLY | O_CREAT | O_TRUNC, 0664);
        else if(ptrredir->token == 2)
            ptrredir->fd = open(ptrredir->path,O_RDONLY , 0777);
        
        if(ptrredir < 0)
            return(0);
        ptrredir = ptrredir->next;
    }
    return(1);   
}


int open_redir(t_cmd **commands)
{
    t_cmd *ptrcmd;
    t_redir *ptrredir;

    ptrcmd = (*commands);
    while(ptrcmd != NULL)
    {
        ptrredir = ptrcmd->redir;
        if(open_fd(&ptrredir) == 0)
            ptrcmd->executable = FALSE;
        else
            ptrcmd->executable = TRUE;
        ptrcmd = ptrcmd->next;
    }
    return(1);
}

int ft_howpipes(t_cmd *comands)
{
    int i;
    i = 0;

    t_cmd *ptr;
    ptr = comands;
    while(ptr != NULL)
    {
        ptr = ptr->next;
        i++;
    }
    return(i);

}

void start_exection(t_cmd **commands,char **env,t_env **cpy)
{
    open_redir(commands);
    ft_magane_executor(commands,env,cpy);
  
}