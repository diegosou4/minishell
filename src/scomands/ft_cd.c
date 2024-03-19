/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/08 11:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// VERIFICAR PARA QUE EU USO ESSA FUNCAO
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
        return(return_error("cd : too many arguments\n"));
    if(comands->args[1] == NULL)
        return(return_error("relative or absuloted path\n"));
    result = chdir(comands->args[1]);
    if(result == 0)
        return(0);
    else
        perror("Error ");
    return(2);
}
 
