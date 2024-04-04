/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:57:57 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:50:35 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	reset_fd(t_bash *bash_boss, int i)
{
	if (i == 1)
		dup2(bash_boss->in, 0);
	if (i == 3)
		dup2(bash_boss->out, 1);
	if (i == 4)
	{
		dup2(bash_boss->in, 0);
		dup2(bash_boss->out, 1);
	}
}

void	dup_fd(t_bash *bash_boss)
{
	bash_boss->in = dup(0);
	bash_boss->out = dup(1);
}

void	init_dup(t_bash *bash_boss)
{
	if (bash_boss->fdin != -1 || bash_boss->fdout != -1)
		dup_fd(bash_boss);
	if (bash_boss->fdin != -1)
		dup2(bash_boss->fdin, 0);
	if (bash_boss->fdout != -1)
		dup2(bash_boss->fdout, 1);
}

void	close_fds(t_bash *bash_boss)
{
	int	i;

	i = 0;
	if (bash_boss->fdout != -1 && bash_boss->fdin != -1)
	{
		i = 4;
		close(bash_boss->fdin);
		close(bash_boss->fdout);
	}
	else if (bash_boss->fdin != -1)
	{
		close(bash_boss->fdin);
		i = 1;
	}
	else if (bash_boss->fdout != -1)
	{
		close(bash_boss->fdout);
		i = 3;
	}
	reset_fd(bash_boss, i);
	bash_boss->fdin = -1;
	bash_boss->fdout = -1;
}

void	close_dup(t_bash *bash_boss)
{
	close(bash_boss->in);
	close(bash_boss->out);
}
