/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:08:24 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 11:08:25 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


int check_builtings(t_cmd *commands)
{
    if(ft_strncmp("pwd",commands->args[0],4) == 0)
        return(1);
    else if (ft_strncmp("cd",commands->args[0],2) == 0)
        return(2);
    else if(ft_strncmp("env",commands->args[0],3) == 0)
        return(3);
    else if(ft_strncmp("export",commands->args[0],6) == 0)
        return(4);
    else if(ft_strncmp("unset", commands->args[0],5) == 0)
        return(5);
    else if(ft_strncmp("echo", commands->args[0],4) == 0)
        return(6);
    else if(ft_strncmp("exit",commands->args[0],4) == 0)
        return(7);
    return(0);
}

// Reutilizar isso na ft_route

int simple_out(t_redir *redir)
{
    int fd;
    t_redir *ptr;

    fd = STDOUT_FILENO;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 1 || ptr->token == 4 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;
    }
    return(fd);
}


int simple_in(t_redir *redir)
{
    int fd;
    t_redir *ptr;
    
    fd = STDIN_FILENO;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 2 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;
    }
    return(fd);
}


void child_builtings(t_cmd **cmd, t_env **cpy)
{
    int check;
    t_redir *redir;
    check = check_builtings((*cmd));
    if(check > 0)
    {
        int in;
        int out;
        in = simple_in((*cmd)->redir);
        out = simple_out ((*cmd)->redir);
        if(in != 0)
            dup2(in,0);
        if(out != 1)
            dup2(out,1);
        execute_builtings(cmd,cpy,check);
        if(in != 0)
            close(in);
        if(out != 1)
            close(out);
    }
}
int execute_builtings(t_cmd **cmd,t_env **cpy, int check)
{
    if(check == 1)
        return(print_pwd());
    else if(check == 2)
        return(ft_cd((*cmd),cpy));
    else if(check == 3)
        return(ft_env((*cpy)));
    else if(check == 4)
        return(ft_export(cpy,(*cmd)));
    else if(check == 5)
        return(ft_unset(cpy,(*cmd)));
    else if(check == 6)
        return(ft_echo((*cmd)));
    else if(check == 7)
    {
        ft_exit((*cmd));
        return(0);
    }
    return(0);
}
