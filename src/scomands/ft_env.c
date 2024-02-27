/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:22:20 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 16:22:21 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void ft_env(char **env)
{
    int i;

    i = 0;
    while(env[i] != NULL)
    {
        printf("%s\n",env[i]);
        i++;
    }
}

void execute_env(char **env, t_cmd *commands)
{
    if(len_darray(commands->args) > 1)
    {
        write(2,"Error two or more arguments!!\n",31);
    }
    ft_env(env);
}