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


int check_builtings(t_cmd *commands)
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
    else if(ft_strncmp("exit",commands->args[0],4) == 0)
        return(7);
    return(0);
}

int execute_builtings(t_bash *executor,int check)
{
    if(check == 1)
        return(print_pwd());
    else if(check == 2)
        return(ft_cd(executor->commands,&executor->cpyenv));
    else if(check == 3)
        return(ft_env(executor->cpyenv));
    else if(check == 4)
        return(ft_export(&executor->cpyenv,executor->commands));
    else if(check == 5)
        return(ft_unset(&executor->cpyenv,executor->commands));
    else if(check == 6)
        return(ft_echo(executor->commands));
    else if(check == 7)
    {
        ft_exit(executor->commands);
        return(0);
    }
    return(0);
}
