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

void close_fderror(t_redir *redir)
{
    t_redir *ptr;

    ptr = redir;
    while(ptr != NULL && ptr->fd > 2)
    {
        close(ptr->fd);
        ptr = ptr->next;
    }

}

void free_redir(t_redir *redir)
{
    t_redir *ptr;

    ptr = redir;

    while(ptr != NULL)
    {
        if(ptr->path != NULL)
            free(ptr->path);
        ptr = ptr->next;
    }



}
void free_all(t_cmd *cmd)
{
    t_cmd *ptr;
    t_cmd *next;

    ptr = cmd;

    while(ptr != NULL)
    {
        next = ptr->next;
        if(ptr->path != NULL)
            free(ptr->path);
        if(ptr->args != NULL)
            freedouble_malloc(ptr->args,(len_darray(ptr->args)) - 1);
        if(ptr->redir != NULL)
            free_redir(ptr->redir);    
        free(ptr);
        ptr = next;
    } 
}

void free_cpyenv(t_env *cpyenv)
{
    t_env *ptr;
    t_env *next;

    ptr = cpyenv;

    while(ptr != NULL)
    {
        if(ptr->key != NULL)
            free(ptr->key);
        if(ptr->value != NULL)
            free(ptr->value);    
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

