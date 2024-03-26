/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:28:38 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 01:36:23 by marvin           ###   ########.fr       */
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

t_env *newexp(char *str, int this, int token)
{
    t_env *cpyenv;
    char *value;
    cpyenv = ft_calloc(sizeof(t_env),1);

    cpyenv->index = this;
    cpyenv->key = ft_strjoin(str,"=");
    cpyenv->value = "''";
    cpyenv->token = token;
    cpyenv->next = NULL;
    return(cpyenv);
}


t_env *newsenv(char *str, int this, int token)
{
    t_env *cpyenv;
    char *value;
    cpyenv = ft_calloc(sizeof(t_env),1);

    cpyenv->index = this;
    cpyenv->key = get_key(str);
    cpyenv->value = ft_strchr(str,61);
    cpyenv->token = token;
    cpyenv->next = NULL;
    return(cpyenv);
}
void addbackenv(char *str,int this,t_env **cpyenv, int token)
{
    t_env *ptr;
    t_env *last;

    last = newsenv(str,this,token);
    if(last == NULL)
        return;
    ptr = (*cpyenv);
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = last;
}


t_env *ft_nenv(char **env, int token)
{
    t_env *cpyenv;
    int index;
    cpyenv = NULL;
    index = 0;
            
    if(env[0] == NULL)
        return(NULL);
    cpyenv = newsenv(env[index],index,token);
    index++;
    while(env[index] != NULL)
    {
        addbackenv(env[index],index,&cpyenv,token);
        index++;
    }
    return(cpyenv);
}

int len_env(t_env *env)
{
    int i;
    t_env *ptr;

    i = 0;
    ptr = env;

    while(ptr != NULL)
    {
        ptr = ptr->next;
        i++;
    }
    return(i);
}
