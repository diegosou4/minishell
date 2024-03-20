/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:01:11 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 17:01:13 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"



void execute_one(t_cmd *command,char **env,t_env **cpy,t_cmd *last)
{
    int check;
    int pid;
    check = check_builtings(command);
    if(check > 0)
    {
        child_bexecutor(command,env,cpy,last); 
        return;
    }
    if(env == NULL)
    {
        ft_putstr_fd("TOME SAL PAPAI\n",2);
        return;
    }
    pid = fork();
    if(pid == 0)
    {
        child_executor(command,env,cpy,last);
        wait(NULL);
    }
}



