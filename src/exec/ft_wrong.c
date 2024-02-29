/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:01:08 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/26 12:01:09 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

// Implementar o here doc
// Implementar o in and out

int case_out(t_redir *redir)
{
    redir->fd = open(redir->path,O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(access(redir->path,R_OK | W_OK ) == 0)
        return(1);
    else
        perror("Error");
    return(0);
}

int case_in(t_redir *redir)
{
    redir->fd = open(redir->path, O_RDONLY, 0777);
    if(access(redir->path,R_OK) == 0)
        return(1);
    else
        perror("Error");
    return(0);
}

int casetoken(t_redir *redir)
{
    if(redir->token == redir_out)
        return(case_out(redir));
    else if(redir->token == redir_in)
        return(case_in(redir));
    return(0);
}


void exec(t_cmd *command,int in, int out,char **env)
{
    if(command->redir->token == 2)
    {
        int pid;
        pid = fork();
        if(pid == 0)
        {
            dup2(command->redir->fd,1);
            execve(command->path,command->args,env);
        }
    }
    close(command->redir->fd);

}


int openredir(t_redir *redir)
{
    t_redir *ptr;

    ptr = redir;

    while(ptr != NULL)
    {
        if(casetoken(ptr) == 1)
            ptr = ptr->next;
        else
        {
            closeredir(redir);
            return(0);
        }  
    }
    return(1);
}
