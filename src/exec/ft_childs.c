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
/*
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
        if(ptr->token == redir_out || ptr->token == append_out)
        {
            close(fd);
            fd = ptr->fd;
        }
            
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
        if(ptr->token == redir_in)
            fd = ptr->fd;
        if(ptr->token == here_doc)
            fd = ft_heredoc(ptr->path);
        ptr = ptr->next;        
    }
    return(fd);
}

int simple_bexecutor(t_cmd *ptrcmd,t_bash *bash_boss)
{
    int check;
    dup_fd(bash_boss);
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
    close_fderror(ptrcmd->redir);
    close_dup(bash_boss);
    return(EXIT_SUCCESS);
}


void child_build(t_cmd *ptrcmd,t_bash *bash_boss, t_cmd *last)
{
    int check;
    bash_boss->exit_status = open_redir_fd(ptrcmd->redir);
    check = check_builtings(ptrcmd);
    if(bash_boss->exit_status == EXIT_FAILURE)
    {
        close_fderror(ptrcmd->redir);
        exit(EXIT_FAILURE);
    }
    bash_boss->fdin = return_in(ptrcmd->redir,ptrcmd,last);
    bash_boss->fdout = return_out(ptrcmd->redir,ptrcmd);
    close_child(&ptrcmd,bash_boss,&last);
    init_dup(bash_boss->fdin,bash_boss->fdout);
    execute_builtings(&ptrcmd,&bash_boss->cpyenv,check);
    close_fds(bash_boss);
    close_fderror(ptrcmd->redir);
    close_dup(bash_boss);
   
    exit(EXIT_SUCCESS);
}
*/
void child_exec(t_cmd *cmd, t_bash *bash_boss, int i)
{
    int in;
    int out;
    in = -1;
    out = -1;
    if(expand_path(&cmd,bash_boss->env) == 1)
        exit(EXIT_FAILURE);
    
    if(!cmd->prev)
    {
        close(cmd->pipes[0]);
        in = -1;
        out = cmd->pipes[1];
    }
    else
    {
        close(cmd->prev->pipes[1]);
        if (cmd->next)
        {
            close(cmd->pipes[0]);
            out = cmd->pipes[1];
        }
        // else
        // {
        //     close(cmd->prev->prev->pipes[0]);
        // }
        in = cmd->prev->pipes[0];
    }
    if(in != -1) 
    {
        dup2(in, STDIN_FILENO);
        close(in);
    }
    if(out != -1)
    {
         dup2(out, STDOUT_FILENO);
        close(out);
    } //ls | cta | wc
    // if (!ptrcmd->pipes)
    // {
    //     if(in != STDIN_FILENO)
    //     {
    //         dup2(in, STDIN_FILENO);
    //     //  close(in);
    //     }   
    //     if(out != STDOUT_FILENO)
    //     {
    //         dup2(out, STDOUT_FILENO);
    //         //close(out);
    //     }    
    // }
    execve(cmd->path,cmd->args,bash_boss->env);

}


void pipes_executor(t_cmd *ptrcmd,t_bash *bash_boss)
{

    int i;
    i = 0;
    t_cmd *ptr;
    ptr = ptrcmd;
    t_cmd *last;
    last = NULL;
    alloc_mypids(bash_boss);
    bash_boss->pipein = -1;
    bash_boss->pipeout = -1;
   ptrcmd->prev = NULL;
   ptrcmd->next->prev = ptrcmd;
   ptrcmd->next->next->prev = ptrcmd->next;
   ptrcmd->next->next->next->prev = ptrcmd->next->next;
    while(ptrcmd != NULL)
    { 
   
        
        if(ptrcmd->next != NULL)
        {
            pipe(ptrcmd->pipes);
            // bash_boss->pipeout = ptrcmd->pipes[1];
            // bash_boss->pipein = ptrcmd->pipes[0];
        }
        // else if(i >= 1)
        // {
        //     bash_boss->pipein = last->pipes[0];
        // }
        bash_boss->pid[i] = fork();
        //printf(" in  %i------\n",ptrcmd->pipes[0]);
      //  printf(" out  %i------\n",ptrcmd->pipes[1]);
        if(bash_boss->pid[i] == 0)
        { 
           printf("%i  filho------------ \n", getpid());
            //  if(i == 2 ) 
            //  {
            //     sleep(1200);
            // }
           child_exec(ptrcmd,bash_boss, i); 
        }
        // if(ptrcmd->next != NULL)
        // {
        //     last = ptrcmd;
        //     close(last->pipes[1]);
        // }
        if (ptrcmd->prev)
        {
            close(ptrcmd->prev->pipes[0]);
            close(ptrcmd->prev->pipes[1]);
        }
        ptrcmd = ptrcmd->next;
        i++;
    }
    // close(last->pipes[0]);
     wait_mypids(bash_boss); 
           
}

