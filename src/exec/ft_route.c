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

void ft_magane_executor(t_bash *bash_boss)
{
    t_cmd *ptrcmd;

    ptrcmd = bash_boss->commands;
    open_pipes(&ptrcmd);
    if(ptrcmd->next == NULL && (check_builtings(ptrcmd) > 0))
        simple_bexecutor(ptrcmd,bash_boss);
    else
        pipes_executor(ptrcmd,bash_boss);

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
    dup_fd(bash_boss);
    ft_magane_executor(bash_boss);
}