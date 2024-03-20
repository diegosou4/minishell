/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pids.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:30:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 15:30:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"

void alloc_mypids(t_bash *bash_boss)
{
    int pipes;
    pipes = ft_howpipes(bash_boss->commands);
    bash_boss->pid = ft_calloc(sizeof(int) , pipes);

}