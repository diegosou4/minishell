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
    char *value = NULL;
    t_env *ptr;

    ptr = *env;
    key = get_key(str);
    if (key == NULL)
        key = ft_strdup(str);
    else
        value = ft_substr(str, ft_strlen(key), ft_strlen(str));
    while (ptr != NULL)
    {
        if (ft_strncmp(ptr->key, key, ft_strlen(key)) == 0)
        {
            free(key);
            if (ft_boolstrchr(str, 61) == 0 || value == NULL || ft_strlen(value) == 0)
            {
                if (value != NULL)
                    free(value); 
                return (EXIT_SUCCESS);
            }
            if (ptr->value != NULL)
                free(ptr->value);
            ptr->value = value;
            ptr->token = token;
            return (EXIT_SUCCESS);
        }
        ptr = ptr->next;
    }
    if (value != NULL)
        free(value); 
    return (EXIT_FAILURE);
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
