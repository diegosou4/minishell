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

int ft_cd(char **env,t_cmd *comands)
{
    char *str;
    int i;
    int result;
    i = 0;
    if(len_darray(comands->args) > 2)
    {
        write(2, "cd: too many arguments\n",43);
        return(4);
    }
    result = chdir(comands->args[1]);
    if(result == 0)
    { 
        return(1);
    }else
    {
        perror("Error ");
    }
    return(3);
}   
