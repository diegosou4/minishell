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

static int flag_compare(char *str)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    if(str == NULL)
        return(0);
    
    if(str[i] == '-')
        flag = 1;
    i++;
    while(str[i] != '\0')
    {
        if(str[i] != 'n')
            flag = 0;
        i++;
    }
    return(flag);
}

int ft_echo(t_cmd *cmd)
{
    int flag;
    flag = 0;
    int i;
    int spaces;

    spaces = 0;
    i = 2;
    flag = flag_compare(cmd->args[1]);
    if(flag == 0)
        i = 1;
    while(cmd->args[i] != NULL)
    {
        if(spaces > 1)
            printf(" ");
        printf("%s",cmd->args[i]);
        spaces++;
        i++;
    }
    if(flag == 0)
        printf("\n");
    return(1);
}




