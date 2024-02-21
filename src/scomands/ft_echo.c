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

void ft_echo(int fd ,char *str, int flag) 
{
    if(flag == 1)
    {
         ft_putstr_fd(str,fd);
         ft_putstr_fd("\n",fd);
    }else
        ft_putstr_fd(str,fd);
}
