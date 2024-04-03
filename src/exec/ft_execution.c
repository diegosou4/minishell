/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:28:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/26 13:28:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void ft_env_null()
{
    ft_putstr_fd("Error env no set\n",2);
}

// Tenho que da free nessa bagaca, n posso esquecer
int check_path2(t_cmd **commands, char **env)
{
    char *str;
    char **arr;
    char *j;
    str = ft_getenv(env,"PATH=",0);    
    arr = mysplit(str,58,47);
    int i;
    i = 0;
    while(arr[i] != NULL)
    {
        j = ft_strjoin(arr[i],(*commands)->args[0]);
        if(access(j, F_OK) == 0)
        {
            (*commands)->path = j;
            return(1);
        }
        free(j);
        i++;
    }
    return(0);
}


void check_path(t_cmd **commands,char **env)
{
    if(*env == NULL)
        return(ft_env_null());
    if(access((*commands)->args[0], F_OK) == 0)
    {
        (*commands)->path = ft_strdup((*commands)->args[0]);
        (*commands)->args[0] = ft_strrchr((*commands)->path,47) + 1;
        return;
    }
    if(check_path2(commands,env) == 1)
            return;
    else
    {
        printf("Error\n");
    }
}


