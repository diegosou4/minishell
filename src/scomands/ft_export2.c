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




int export_env(t_env **env,char *str)
{
    t_env *ptr;
    char *value;
    char *key;
    key = NULL;
    int len;

    value = ft_strchr(str, '=');
    
    if(value != NULL)
    {
        len = ft_strlen(str) - ft_strlen(value);
        printf("len %i \n",len);
    }
    printf("key %s value %s \n",key,value);
    
    return(EXIT_SUCCESS);
}