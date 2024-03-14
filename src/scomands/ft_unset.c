/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:33:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 14:33:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void update_index(t_env **env)
{
    int i;
    i = 0;
    t_env *ptr;

    ptr = (*env);
    while(ptr != NULL)
    {
        ptr->index = i;
        i++;
        ptr = ptr->next;
    }
}

void ft_removeinenv(t_env **env, int index)
{

    t_env *ptr;
    t_env *prev;
    t_env *next;
    ptr = (*env);
    while(index != 0)
    {
        prev = ptr;
        ptr = ptr->next;
        index--;
    }
    if(ptr->next != NULL)
        next = ptr->next;
    else
        next = NULL;
    if(prev != NULL)
        prev->next = next;
    else
        *env = next;
}

int ft_unset(t_env **env,t_cmd *commands)
{
    int index;
    char *str;
    index = ft_strintchr(commands->args[1],61);
    if(ft_strncmp("_=",commands->args[1],2) == 0)
        return(2);
    if(*env == NULL)
        return(2);
    if(index == -1)
    {
        index = ft_indexinenv(*env,commands->args[1]);
        if(index == -1)
            return(2);
        ft_removeinenv(env,index);
        update_index(env);
    }
    return(0);
}
