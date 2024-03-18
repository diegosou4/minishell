/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:25:54 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 12:25:56 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int ft_echo(t_cmd *cmd) 
{
    int flag;
    flag = 0;
    int i;
        
    i = 2;
    flag = ft_strncmp(cmd->args[1],"-n",ft_strlen(cmd->args[1]));
    if(flag != 0)
        i = 1;
    while(cmd->args[i] != NULL)
    {
        printf("%s",cmd->args[i]);
        i++;
    }
    if(flag != 0)
        printf("\n");
    return(1);
}



