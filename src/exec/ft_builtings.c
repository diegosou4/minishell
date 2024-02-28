/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:08:24 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 11:08:25 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int check_builtings(t_cmd *commands, char **env)
{
    if(ft_strncmp("pwd",commands->args[0],4) == 0)
        return(1);
    else if (ft_strncmp("cd",commands->args[0],2) == 0)
        return(2);
    else if(ft_strncmp("env",commands->args[0],3) == 0)
        return(3);
    else if(ft_strncmp("export",commands->args[0],6) == 0)
        return(4);
    else if(ft_strncmp("unset", commands->args[0],5) == 0)
        return(5);
    else if(ft_strncmp("echo", commands->args[0],4) == 0)
        return(6);
    return(0);
}