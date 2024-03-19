/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:28:38 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 18:28:39 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char *get_key(char *str)
{
    char *key;
    int i;
    i = 0;
    while(str[i] != '\0')
    {   
        if(str[i] == 61)
        {
            key = ft_substr(str,0,i);
            return(key);
        }
        i++;
    }
    return(NULL);
}

t_env *newsenv(char *str, int this)
{
    t_env *cpyenv;
    char *value;
    cpyenv = ft_calloc(sizeof(t_env),1);

    cpyenv->index = this;
    cpyenv->key = get_key(str);
    cpyenv->value = ft_strchr(str,61);
    cpyenv->next = NULL;
    return(cpyenv);
}
void addbackenv(char *str,int this,t_env **cpyenv)
{
    t_env *ptr;
    t_env *last;

    last = newsenv(str,this);
    if(last == NULL)
        return;
    ptr = (*cpyenv);
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = last;
}

void print_env(t_env *env)
{
    t_env *ptr;

    ptr = env;

    while(ptr != NULL)
    {
        printf("Index: %i \n",ptr->index);
        printf("Key: %s \n", ptr->key);
        printf("Value: %s \n", ptr->value);
        ptr = ptr->next;
    }
}
t_env *ft_nenv(char **env)
{
    t_env *cpyenv;
    int index;
    cpyenv = NULL;
    index = 0;

    if(env[0] == NULL)
        return(NULL);
    cpyenv = newsenv(env[index],index);
    index++;
    while(env[index] != NULL)
    {
        addbackenv(env[index],index,&cpyenv);
        index++;
    }
    return(cpyenv);
}
