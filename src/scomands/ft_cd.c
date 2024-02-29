/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 16:20:28 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char *ft_returnpath(t_env *env,char *this)
{   
    t_env *ptr;
    ptr = env;
    while(ptr != NULL)
    {
        if(ptr->key == this)
            return(ft_strdup(ptr->value));
        ptr = ptr->next;
    }
    return(NULL);
}

int ft_cd(t_cmd *comands,t_env **env)
{
    int result;
    if(len_darray(comands->args) > 2)
    {
        write(2, "cd: too many arguments\n",43);
        return(4);
    }
    if(comands->args[1] == NULL)
    {
        write(2,"relative or absuloted path\n",28);
        return(4);
    }
    result = chdir(comands->args[1]);
    if(result == 0)
    {
        return(1);
    }
    else
        perror("Error ");
    return(3);
}
 
