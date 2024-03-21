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

int simple_bexecutor(t_cmd *ptrcmd,t_bash *bash_boss)
{
    int check;
    bash_boss->exit_status = open_redir_fd(ptrcmd->redir);
    check = check_builtings(ptrcmd);
    if(bash_boss->exit_status == EXIT_FAILURE)
    {
        // fechar o que eu abri
        return(0);
    }
    bash_boss->fdin = return_in(ptrcmd->redir,ptrcmd,(t_cmd*)0);
    bash_boss->fdout = return_out(ptrcmd->redir,ptrcmd);
    init_dup(bash_boss->fdin,bash_boss->fdout);
    execute_builtings(&ptrcmd,&bash_boss->cpyenv,check);
    close_fds(bash_boss);
    reset_fd(bash_boss); 
    return(EXIT_SUCCESS);
}


void child_build(t_cmd *ptrcmd,t_bash *bash_boss, t_cmd *last)
{
    int check;
    bash_boss->exit_status = open_redir_fd(ptrcmd->redir);
    check = check_builtings(ptrcmd);
    if(bash_boss->exit_status == EXIT_FAILURE)
    {
        // arrumar
        exit(EXIT_FAILURE);
    }
    bash_boss->fdin = return_in(ptrcmd->redir,ptrcmd,last);
    bash_boss->fdout = return_out(ptrcmd->redir,ptrcmd);
    init_dup(bash_boss->fdin,bash_boss->fdout);
    execute_builtings(&ptrcmd,&bash_boss->cpyenv,check);
    close_fds(bash_boss);
    exit(EXIT_SUCCESS);
}

void child_exec(t_cmd *ptrcmd,t_bash *bash_boss,t_cmd *last)
{
    bash_boss->exit_status = open_redir_fd(ptrcmd->redir);
    expand_path(&ptrcmd,bash_boss->env);     
    if(bash_boss->exit_status == EXIT_FAILURE)
    {
        // arrumar
        exit(EXIT_FAILURE);
    }
  
    bash_boss->fdin = return_in(ptrcmd->redir,ptrcmd,last);
    bash_boss->fdout = return_out(ptrcmd->redir,ptrcmd);
    init_dup(bash_boss->fdin,bash_boss->fdout);
    execve(ptrcmd->path,ptrcmd->args,bash_boss->env);
}
// Alocar pids
// 

void pipes_executor(t_cmd *ptrcmd,t_bash *bash_boss)
{
    t_cmd *last;
    last = NULL;
    int i;
    i = 0;
    alloc_mypids(bash_boss);
    while(ptrcmd != NULL)
    {
        bash_boss->pid[i] = fork();
        if(bash_boss->pid[i] == 0)
        {      
        if(check_builtings(ptrcmd) == 0)
            child_exec(ptrcmd,bash_boss,last);       
        else
            child_build(ptrcmd,bash_boss,last);
        }
        last = ptrcmd;
        ptrcmd = ptrcmd->next;
        close(last->pipesfd[1]);
        waitpid(bash_boss->pid[i],&bash_boss->exit_status,0);
        i++;
    }
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