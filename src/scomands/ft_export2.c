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



int key_exist(t_env **env, char *str, int token)
{
    char *key;
    char *value;
    t_env *ptr;
 
    ptr = (*env);
    key = get_key(str);
    value = ft_strchr(str,61);
    if(key == NULL)
        key = ft_strdup(str);

    while(ptr != NULL)
    {       
        if(ft_strncmp(ptr->key,key,ft_strlen(ptr->key)) == 0)
        {   
            if(value == NULL)
                return(1);
            if(ptr->value != NULL)
                free(ptr->value);
            ptr->value = ft_strdup(value);
            ptr->token = token;
            return(1);
        }
        ptr = ptr->next;
    }
    return(0);
}



int export_env(t_env **env,char *str)
{
    int len;
    int token;

    token = 3;
    if(ft_boolstrchr(str,61) == 1)
        token = 2;
  
    if(key_exist(env,str,token) == 0)
       addbackenv(str,env,token);
    return(EXIT_SUCCESS);
}
