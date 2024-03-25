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
    /*if(ptrcmd->next == NULL && (check_builtings(ptrcmd) > 0))
        simple_bexecutor(ptrcmd,bash_boss); */
    pipes_executor(ptrcmd,bash_boss);
    //free_commands(bash_boss.commands);

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
    bash_boss->pipein = -1;
    bash_boss->pipeout= -1;
    ft_magane_executor(bash_boss);
}