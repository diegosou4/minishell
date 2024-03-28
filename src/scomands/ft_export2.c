/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:17 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/26 16:01:19 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

static void change_value(char **key,char **value,char *str)
{
    *key = get_key(str);
    if (*key == NULL)
        *key = ft_strdup(str);
    else
        *value = ft_substr(str, ft_strlen(*key), ft_strlen(str));
}

static int change_key(t_env **ptr,char *value, int token)
{
     if ((*ptr)->value != NULL)
            free((*ptr)->value);
        (*ptr)->value = value;
        (*ptr)->token = token;
        return(EXIT_SUCCESS);
}

static int free_value(char *value,int exit)
{
    if (value != NULL)
        free(value);
    return(exit); 
}

int key_exist(t_env **env, char *str, int token)
{
    char *key;
    char *value;
    t_env *ptr;

    value = NULL;
    ptr = *env;
    change_value(&key,&value,str);
    while (ptr != NULL)
    {
        if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0)
        {
            free(key);
            if (ft_boolstrchr(str, 61) == 0 || value == NULL || ft_strlen(value) == 0)
               return(free_value(value,EXIT_SUCCESS));
            return (change_key(&ptr,value,token));
        }
        ptr = ptr->next;
    }
    free(key);
    return (free_value(value,EXIT_FAILURE));
}


int export_env(t_env **env,char *str)
{
    int token;
    token = 3;
    if(ft_boolstrchr(str,61) == 1)
        token = 2;
    if(key_exist(env,str,token) == 1)
      addbackenv(str,env,token);
    return(EXIT_SUCCESS);
}
