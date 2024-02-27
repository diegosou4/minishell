/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:38:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 11:38:36 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void free_redirects(t_redir *redir)
{
    t_redir *ptr;
    t_redir *next;

    ptr = redir;

    while(ptr != NULL)
    {
        next = ptr->next;
        free(ptr->path);
        if(ptr->fd >= 3 )
            close(ptr->fd);
        ptr = next;
    }
}
int len_darray(char **arr)
{
    int i;
    i = 0;
    while(arr[i] != NULL)
        i++;
    return(i);
}

void free_commands(t_cmd *comands)
{
    t_cmd *ptr;
    t_cmd *next;
    ptr = comands;

    while(ptr != NULL)
    {
        next = ptr->next;
        if(ptr->redir != NULL)
            free_redirects(ptr->redir);
        free(ptr->path);
       // freedouble_malloc(ptr->args,(len_darray(ptr->args)) - 1);
        ptr = next;
    }
}

void closeandfree(t_redir *redir)
{
    free(redir->path);
    close(redir->fd);
    free(redir);
}
int closeredir(t_redir *redir)
{
    t_redir *ptr = redir;
    t_redir *next;

    while(ptr != NULL)
    {
        next = ptr->next;
        closeandfree(ptr);
        ptr = next;
    }
    return (0);
}