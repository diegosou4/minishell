/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeroute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:45:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 16:51:19 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	free_pids(t_bash *bash_boss)
{
	if (bash_boss->pid)
	{
		free(bash_boss->pid);
		bash_boss->pid = NULL;
	}
}

void	free_here(t_bash *bash_boss)
{
	ft_free_env_list(bash_boss->cpyenv);
	ft_free_double_pointers(bash_boss->env);
	ft_free_cmd_structure(bash_boss->commands);
}
