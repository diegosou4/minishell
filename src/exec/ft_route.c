/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 19:27:50 by marvin           ###   ########.fr       */
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

void close_pipes(t_cmd **cmd)
{
    t_cmd *ptr;

    ptr = (*cmd);
    while(ptr != NULL)
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
    {
        fd = last->pipesfd[0];
    }
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 2 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;        
    }
    return(fd);
}
/*
int child_executor(t_bash *executor,t_cmd *ptrcmd,t_bash *bash_boss)
{
    int fdin;
    int fdout;
  //  executor->exit_status = open_redir_fd(executor);
    if(expand_path(&executor->commands,bash_boss->env) == EXIT_FAILURE)
        exit(EXIT_FAILURE);
    if(return_error_exec(executor) == 1)
        exit(EXIT_FAILURE);
    fdin = return_in(executor->commands->redir,ptrcmd,executor->last);;
    fdout = return_out(executor->commands->redir,ptrcmd); 
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
         close(fdout);
    if(fdin != 0)
        close(fdin);
    execve(executor->commands->path,executor->commands->args,executor->env);
    return(1);
}
void child_bexecutor(t_bash *executor,t_cmd *ptrcmd,t_bash *bash_boss)
{
    int check;
    int fdin;
    int fdout;
    executor->exit_status = open_redir_fd(executor);
    check = check_builtings(ptrcmd);
 
    fdin = return_in(executor->commands->redir,ptrcmd,executor->last);;
    fdout = return_out(executor->commands->redir,ptrcmd);
    dup2(fdin,0);
    dup2(fdout,1);
    if(fdout != 1)
        close(fdout);
    if(fdin != 0)
        close(fdin);  
    //execute_builtings(executor,check);
    exit(EXIT_SUCCESS);
}

*/

void closeoutpipe(t_cmd **ptr)
{
    close((*ptr)->pipesfd[1]);
}


t_cmd *return_current(t_cmd *ptrcmd)
{
    t_cmd *curr;

    curr = ft_calloc(sizeof(t_cmd),1);

    curr->args = ptrcmd->args;
    curr->executable = 1;
    curr->redir = ptrcmd->redir;
    return(curr);
}

void init_mybash(t_bash *bash_boss,t_cmd *curr,t_bash *executor)
{
    executor->commands = return_current(curr);
    executor->env = bash_boss->env;
    executor->cpyenv = bash_boss->cpyenv;
 }


int simple_bexecutor(t_cmd *ptrcmd,t_bash *bash_boss)
{
    int check;
    int fdin;
    int fdout;
    bash_boss->exit_status = open_redir_fd(ptrcmd->redir);
    check = check_builtings(ptrcmd);
    if(bash_boss->exit_status == EXIT_FAILURE)
        return(0);
    fdin = return_in(ptrcmd->redir,ptrcmd,(t_cmd*)0);
    fdout = return_out(ptrcmd->redir,ptrcmd);
    dup2(fdin,0);
    dup2(fdout,1);
    execute_builtings(&ptrcmd,&bash_boss->cpyenv,check);
    close(fdout);
    close(fdin);
    dup2(bash_boss->in, 0); 
    dup2(bash_boss->out, 1); 
    return(EXIT_SUCCESS);
}

/*
void while_commands(t_bash *executor,t_bash *bash_boss,t_cmd *ptrcmd)
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
        ptrcmd = ptrcmd->next;
        waitpid(bash_boss->pid[i],&i,0);
        i++;
        if(ptrcmd != NULL)
            closeoutpipe(&executor->last);
    }  
}*/
void close_ptr(t_redir **redir)
{
    t_redir *ptr;

    ptr = (*redir);
    printf("Chega aqui e fecha");
    while(ptr != NULL)
    {
        close(ptr->fd);
        ptr = ptr->next;
    }
}


void ft_magane_executor(t_bash *bash_boss)
{
    t_cmd *ptrcmd;
    t_cmd *last;
    last  = NULL;
    ptrcmd = bash_boss->commands;
    open_pipes(&ptrcmd);
    if(ptrcmd->next == NULL && (check_builtings(ptrcmd) > 0))
    {
        simple_bexecutor(ptrcmd,bash_boss);
    }
    //free_commands(bash_boss.commands);
    close_pipes(&bash_boss->commands);
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
        if(ptrredir->token == redir_out)
            ptrredir->fd = open(ptrredir->path,O_WRONLY | O_CREAT | O_TRUNC, 0664);
        else if(ptrredir->token == redir_in)
            ptrredir->fd = open(ptrredir->path,O_RDONLY , 0777);
        else if(ptrredir->token == append_out)
            ptrredir->fd = open(ptrredir->path,O_WRONLY | O_CREAT | O_APPEND, 0664);
        if(ptrredir->fd < 0)
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

void start_execution(t_bash *bash_boss)
{
    bash_boss->in = dup(0);
    bash_boss->out = dup(1);
    ft_magane_executor(bash_boss);
}