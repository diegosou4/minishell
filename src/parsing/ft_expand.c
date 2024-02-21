/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:54:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/21 17:54:56 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"


void ft_expand(t_cmd **commads, char **cpyenv)
{
    t_cmd *ptr;
    ptr = (*commads);
    char *path;
    char *blackslash;
    if(!ptr)
        return;
    path = ft_getenv(cpyenv, "PATH=/");
    while(ptr != NULL)
    {
        blackslash = ft_strjoin("/",ptr->args[0]);
        ptr->path = ask_acess(blackslash,path);
        free(blackslash);
        ptr = ptr->next;
    }
    t_cmd *newptr;
    newptr = (*commads);
    while(newptr != NULL)
    {
        printf("PATH: %s\n", newptr->path);
        newptr = newptr->next;
    }
}
