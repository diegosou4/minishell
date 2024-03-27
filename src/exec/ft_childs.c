
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

int return_in(t_cmd *cmd, t_bash *bash_boss)
{
    t_redir *ptr;
    int fd;
    fd = -1;
    ptr = cmd->redir;
    int pipesfd[2];
    if(ptr == NULL)
        return(-1);
    while(ptr != NULL)
    {
        if(ptr->token == redir_in || ptr->token == here_doc)
        {
            if(fd != -1)
                close(fd);
            if(ptr->token == here_doc)
            {
                pipe(pipesfd);
                ft_heredoc(ptr->path,pipesfd[0],pipesfd[1],bash_boss);
                fd = pipesfd[0];
            }
            else    
                fd = open_in(ptr->path);
            if(fd < 0)
            {
                // execucao nao deve funcionar;
            } 
        }
         ptr = ptr->next; 
    }
    return(fd);
}

int return_out(t_cmd *cmd)
{
    t_redir *ptr;
    int fd;
    fd = -1;
    ptr = cmd->redir;
    if(ptr == NULL)
        return(-1);
    while(ptr != NULL)
    {
        if(ptr->token == redir_out || ptr->token == append_out)
        {
            if(fd != -1)
                close(fd);
            if(ptr->token == redir_out)
                fd = open_out(ptr->path);
            else
                fd = open_append(ptr->path);
            if(fd < 0)
            {
             // execucao nao deve funcionar;
            }
        }
    
        ptr = ptr->next;
    }
    return(fd);
}


void child_exec(t_cmd *cmd, t_bash *bash_boss)
{
    bash_boss->fdout = return_out(cmd);
    bash_boss->fdin = return_in(cmd,bash_boss);
    if(expand_path(&cmd,bash_boss->env) == 1)
        fail_expander(bash_boss,cmd);
    if(sizepipe(bash_boss->commands) != 1)
        care_inchild(cmd,bash_boss);
    redir_inchild(bash_boss);
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

void child_build(t_cmd *cmd, t_bash *bash_boss)
{
    
    int check;
    check = check_builtings(cmd);
    bash_boss->fdout = return_out(cmd);
    bash_boss->fdin = return_in(cmd,bash_boss);
    if(expand_path(&cmd,bash_boss->env) == 1)
        exit(EXIT_FAILURE);
    if(sizepipe(bash_boss->commands) != 1)
        care_inchild(cmd,bash_boss);
    redir_inchild(bash_boss);
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
    execute_builtings(&cmd,&bash_boss->cpyenv,check);
    exit(EXIT_SUCCESS);
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
            if(check_builtings(ptrcmd) == 0)
                 child_exec(ptrcmd,bash_boss);
            child_build(ptrcmd,bash_boss);
        }
        care_myprev(ptrcmd);
        ptrcmd = ptrcmd->next;
        i++;
    }
     wait_mypids(bash_boss);     
}

