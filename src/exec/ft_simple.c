/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:54:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/05 11:54:15 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int have_out(t_redir *redir)
{
    int have;
    have = 0;
    t_redir *ptr;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 1 | ptr->token == 4)
            have++;
        ptr = ptr->next;
    }
    return(have);
}



// IF not have redirect
// And One command;

void exec_simple(t_cmd *command,char **env, int *fd)
{
    int pid;

    pid = fork();
    if(pid == 0)
    {
        dup2(fd[1],1);
        execve(command->path,command->args,NULL);
        exit(0);
    }
}

void exec_pipe(t_cmd *command,char **env)
{
    int fd[2];
    pipe(fd);

    exec_simple(command,env,fd);
    close(fd[1]);
    wait(NULL);
    char *str;
    str = get_next_line(fd[0]);
    while(str != NULL)
    {
        printf("%s",str);
        free(str);
        str = get_next_line(fd[0]);
    }
    free(str);
    close(fd[0]);    
}