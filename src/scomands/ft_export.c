/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:22:43 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:44 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

int have_inenv(char **env, char *str)
{
    int i;
    i = 0;
    int index;
    char *newstr;
    index = ft_strintchr(str,61);
    newstr = ft_substr(str,0,index +1);
    i = index_env(env,newstr);
    if(i != -1)
    {
        free(env[i]);
        env[i] = str;
        return(1);
    }
    return(0);
}


void ft_export(char **env,t_cmd *commands)
{
    int i;
    i = 0;
    if(have_inenv(env,commands->args[1]) == 1)
        return;

}