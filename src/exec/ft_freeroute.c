/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeroute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:45:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 10:55:20 by diegmore         ###   ########.fr       */
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

static void	custom_ft_free_line(t_line *line)
{
	if (line->line_text)
		free(line->line_text);
	if (line->color_line)
		free(line->color_line);
	if (line->line)
		free(line->line);
}

void	free_here(t_bash *bash_boss)
{
	custom_ft_free_line(bash_boss->line);
	ft_free_env_list(bash_boss->cpyenv);
	ft_free_double_pointers(bash_boss->env);
	ft_free_cmd_structure(bash_boss->commands);
}
