/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 15:16:20 by marvin           ###   ########.fr       */
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
        if(ptr->token == redir_out || ptr->token == append_out || ptr->token == inandout)
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

void child_executor(t_bash *executor)
{

    int fdin;
    int fdout;
    fdin = executor->in;
    fdout = executor->out; 
   
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
         close(fdout);
    if(fdin != 0)
        close(fdin);
    execve(executor->commands->path,executor->commands->args,executor->env);
    
}
void child_bexecutor(t_bash *executor)
{
    int check;
    int fdin;
    int fdout;
    check = check_builtings(executor->commands);

    fdin = executor->in;
    fdout = executor->out; 
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
        close(fdout);
    if(fdin != 0)
        close(fdin);  
    execute_builtings(&executor->commands,&executor->cpyenv,check);
   
    close(fdin);
    close(fdout);
    exit(0);
}



void closeoutpipe(t_cmd **ptr)
{
    close((*ptr)->pipesfd[1]);
}

void init_mybash(t_bash *bash_boss,t_cmd *curr,t_bash *executor)
{
    
    executor->in = return_in(curr->redir,curr,executor->last);
    executor->out = return_out(curr->redir,curr);
    executor->commands = curr;
    executor->env = bash_boss->env;
    executor->cpyenv = bash_boss->cpyenv;

 }

void ft_magane_executor(t_bash bash_boss)
{
    int pid;
    t_cmd *ptrcmd;
    t_bash executor;
    executor.last = NULL;
    ptrcmd = bash_boss.commands;

    while(ptrcmd != NULL)
    {
        init_mybash(&bash_boss,ptrcmd,&executor);
        pid = fork();
        if(pid == 0)
        {
            if(check_builtings(ptrcmd) == 0)
                child_executor(&executor);
            else
                child_bexecutor(&executor);
                close(bash_boss.in);
                close(bash_boss.out);
        }
        executor.last = ptrcmd;
        closeoutpipe(&executor.last);
        ptrcmd = ptrcmd->next;
    }
    wait(NULL);
    close_pipes(&bash_boss.commands);
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

void start_execution(t_bash bash_boss)
{

     open_redir(&bash_boss.commands);
    expand_path(&bash_boss.commands,bash_boss.env);
    open_pipes(&bash_boss.commands);
    ft_magane_executor(bash_boss);
   // ft_free_cmd_structure(bash_boss.commands);
}