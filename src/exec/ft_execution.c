/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:28:19 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 16:50:46 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_env_null(void)
{
	ft_putstr_fd("Error env no set\n", 2);
}

t_file_struct	*get_file_num(void)
{
	static t_file_struct	instance;

	return (&instance);
}

void	fail_expander(t_bash *bash_boss)
{
	if (bash_boss->fdin != -1)
		close(bash_boss->fdin);
	if (bash_boss->fdout != -1)
		close(bash_boss->fdout);
	if (bash_boss->pipein != -1)
		close(bash_boss->pipein);
	if (bash_boss->pipeout != -1)
		close(bash_boss->pipeout);
	free_here(bash_boss);
	free_pids(bash_boss);
	get_file_num()->exit_code = 127;
	exit(127);
}
