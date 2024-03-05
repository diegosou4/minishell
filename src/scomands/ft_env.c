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

void ft_env(t_env *env)
{
    t_env *ptr;

    ptr = env;
    if(env ==  NULL)
        return;
    while(ptr != NULL)
    {
        if(ptr->token == 1)
            printf("%s%s\n",ptr->key,ptr->value);
        ptr = ptr->next;
    }
}

void execute_env(t_env *env, t_cmd *commands)
{
    if(len_darray(commands->args) > 1)
        write(2,"Error two or more arguments!!\n",31);
    else
        ft_env(env);
}