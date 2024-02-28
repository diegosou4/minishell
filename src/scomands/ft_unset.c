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


char **ft_unsetinarr(char **env,int index)
{
    int i;
    i = 0;
    int j;
    j = 0;
    char **new_env;
    new_env = ft_calloc(sizeof(char*),len_darray(env));
    while(env[i] != NULL)
    {
        if(i == index)
            i++;
        if(env[i] != NULL)
        {
            new_env[j] = env[i];
            i++;
            j++;
        }
    }
    return(new_env);
}



void ft_unset(char ***env,t_cmd *commands)
{
    int index;
    char **new_env;
    new_env = NULL;
    index = index_env(*env,commands->args[1]);
    if(index != -1)
    {
        new_env = ft_unsetinarr(*env,index);
        *env = new_env;
    }
}