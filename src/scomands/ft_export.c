/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:22:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:44 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

int ft_indexinenv(t_env *env,char *this)
{
    int index;
    index = 0;
    t_env *ptr;
    ptr = env;
    
    if(env == NULL)
        return(-1);
    while(ptr != NULL)
    {
        if(strncmp(ptr->key,this, ft_strlen(ptr->key)) == 0)
            return(index);
        ptr = ptr->next;
        index++;
    }
    return(-1);
}

int ft_haveinenv(t_env *env, char *str)
{
    int i;
    int j;
    char *newstr;
    t_env *ptr;
    ptr = env;
    if(env == NULL)
        return(0);
    i = ft_strintchr(str,61);
    newstr = ft_substr(str,0,i);
    j = ft_indexinenv(env,newstr);
    if(j != -1)
    {
        while(j != 0)
        {
            ptr = ptr->next;
            j--;
        }
        ptr->value = ft_strchr(str,61);
        return(1);
    }
    return(0);
}

void ft_putinlast(t_env **env,char *this)
{
    int i;
    t_env *ptr;
    t_env *last;
    t_env *pen ;
    ptr = (*env);
    while(ptr->next != NULL)
    {
        pen = ptr;
        ptr = ptr->next;
    }
    i = ptr->index;
    last = newsenv(this,i);
    if(pen != NULL)
    {
        pen->next = last;
        last->next = ptr;
    }
    ptr->index += 1;
    update_index(env);      
}


void ft_export(t_env **env,t_cmd *commands)
{
    if(ft_strintchr(commands->args[1],61) != 0)
    {       
        if(ft_haveinenv(*env,commands->args[1]) == 1)
            return;
        else if(*env == NULL)
            *env = newsenv(commands->args[1],0); 
        else
         ft_putinlast(env,commands->args[1]);   
    }
}
