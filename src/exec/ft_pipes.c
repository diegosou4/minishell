/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:48:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:48:58 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	sizepipe(t_cmd *commands)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = commands;
	while (ptr != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

void	set_pipes(t_cmd *ptrcmd)
{
	if (ptrcmd->next != NULL)
		pipe(ptrcmd->pipes);
}

void	care_myprev(t_cmd *ptrcmd)
{
	if (ptrcmd->prev)
	{
		close(ptrcmd->prev->pipes[0]);
		close(ptrcmd->prev->pipes[1]);
	}
}

void	care_inchild(t_cmd *current, t_bash *bash_boss)
{
	if (!current->prev)
	{
		close(current->pipes[0]);
		bash_boss->pipein = -1;
		bash_boss->pipeout = current->pipes[1];
		return ;
	}
	close(current->prev->pipes[1]);
	if (current->next)
	{
		close(current->pipes[0]);
		bash_boss->pipeout = current->pipes[1];
	}
	bash_boss->pipein = current->prev->pipes[0];
}

void	redir_inchild(t_bash *bash_boss)
{
	if (bash_boss->fdout == -1)
		bash_boss->fdout = bash_boss->pipeout;
	else
	{
		if(bash_boss->pipeout != -1)
			close(bash_boss->pipeout);
	}
	if (bash_boss->fdin == -1)
		bash_boss->fdin = bash_boss->pipein;
	else
	{
		if(bash_boss->pipein)
			close(bash_boss->pipein);
	}
		
}
