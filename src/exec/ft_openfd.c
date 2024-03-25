/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 11:17:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int open_out(char *path)
{
    int fd;

    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd < 0)
    {
        printf_error_fd(strerror(errno),path);
        return(fd);
    }
    return(fd);
}

int open_in(char *path)
{
    int fd;

    fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        printf(" da erro aqui");
        printf_error_fd(strerror(errno),path);
        return(fd);
    }
    return(fd);
}

int open_append(char *path)
{
    int fd;

    fd = open(path,O_WRONLY | O_CREAT | O_APPEND, 0664);
    if(fd < 0)
    {
        printf_error_fd(strerror(errno),path);
        return(fd);
    }
    return(fd);
}

int open_fd(t_redir **redirect)
{
    t_redir *ptrredir;

    ptrredir = (*redirect);
    while(ptrredir != NULL)
    {
        if(ptrredir->token == redir_out)
            ptrredir->fd = open_out(ptrredir->path);
        else if(ptrredir->token == redir_in)
            ptrredir->fd = open_in(ptrredir->path);
        else if(ptrredir->token == append_out)
            ptrredir->fd = open_append(ptrredir->path);
        if(ptrredir->fd < 0 && ptrredir->token != here_doc)
            return(0);
        ptrredir = ptrredir->next;
    }
    return(1);   
}


int open_redir_fd(t_redir *redir)
{
    t_redir *ptr;
    int flag;
    ptr = redir;
    if(ptr == NULL)
        return(EXIT_SUCCESS);
    flag = open_fd(&ptr);
    if(flag == 0)
        return(EXIT_FAILURE);

    return(EXIT_SUCCESS);
}