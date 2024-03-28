/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:11:00 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/28 16:11:02 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

char *get_valuepwd(t_env **env, char *value)
{
    t_env *ptr;
    char *key;
    char *val;
    if(env == NULL)
        return(NULL);
    ptr = (*env);
    key  = ft_strdup(value);
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->key,key,ft_strlen(key)) == 0)
        {   
            if(key != NULL)
                free(key);
            val = ft_strdup(ptr->value);
            return(val);
        }
        ptr = ptr->next;
    }
    if(key != NULL)
        free(key);
    return(NULL);
}