
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
            key = ft_substr(str,0,(i + 1));
            return(key);
        }
        i++;
    }
    return(NULL);
}

t_env *newsenv(char *str, int token)
{
    t_env *cpyenv;
    char *v;
    char *key;
    char *value;

    key = get_key(str);
    cpyenv = ft_calloc(sizeof(t_env),1);
    cpyenv->value = NULL;
    if (key == NULL)
        key = ft_strjoin(str,"=");
    else
        cpyenv->value = ft_substr(str,ft_strlen(key),ft_strlen(str));   
    cpyenv->key = key;
    cpyenv->token = token;
    cpyenv->next = NULL;
    return(cpyenv);
}
void addbackenv(char *str,t_env **cpyenv, int token)
{
    t_env *ptr;
    t_env *last;
    
    if(str == NULL)
        return;
    ptr = (*cpyenv);
    if(ptr == NULL)
    {
        *cpyenv = newsenv(str,token);
        
        return;
    }
    last = newsenv(str,token);
    if(last == NULL)
        return;    
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
    cpyenv = newsenv(env[index],token);
    index++;
    while(env[index] != NULL)
    {
        addbackenv(env[index],&cpyenv,token);
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

