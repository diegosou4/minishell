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


static char *ft_strcpy(char *dest, const char *src) 
{
    while (*src) 
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}

char **ft_arrcpy(char **str) 
{
    int i = 0;
    int j = 0;
    char **str_copy ;
    if (!str || !str[0])
        return NULL;    
    while (str[i]) 
        i++;    
    str_copy = (char **)malloc((i + 1) * sizeof(char *));
    if (!str_copy) 
        return NULL;
    while (j < i) 
    {
        int len = strlen(str[j]);
        str_copy[j] = (char *)malloc((len + 1) * sizeof(char));
        if (!str_copy[j]) {
            // memory allocation failed, free previously allocated memory
            for (int k = 0; k < j; k++) {
                free(str_copy[k]);
            }
            free(str_copy);
            return NULL;
        }
        ft_strcpy(str_copy[j], str[j]);
        j++;
    }
    return(str_copy);
}


