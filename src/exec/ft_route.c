/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 15:56:42 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	simple_bexecutor(t_cmd *ptrcmd, t_bash *bash_boss, int check)
{
	return_intout(ptrcmd, bash_boss);
	if (ptrcmd->executable == 0)
		return (EXIT_FAILURE);
	init_dup(bash_boss);
	execute_builtings(&ptrcmd, &bash_boss->cpyenv, check);
	close_fds(bash_boss);
	close_fderror(ptrcmd->redir);
	return (EXIT_SUCCESS);
}

void	ft_magane_executor(t_bash *bash_boss)
{
	t_cmd	*ptrcmd;
	int		check;

	ptrcmd = bash_boss->commands;
	check = check_builtings(ptrcmd);
	if (ptrcmd->next == NULL && check > 0 && check <= 7)
		simple_bexecutor(ptrcmd, bash_boss, check);
	else
		pipes_executor(ptrcmd, bash_boss);
}

int	ft_howpipes(t_cmd *comands)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = comands;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	pipes_executor(t_cmd *ptrcmd, t_bash *bash_boss)
{
	int		i;
	t_cmd	*ptr;

	i = 0;
	ptr = ptrcmd;
	alloc_mypids(bash_boss);
	while (ptrcmd != NULL)
	{
		set_pipes(ptrcmd);
		bash_boss->pid[i] = fork();
		if (bash_boss->pid[i] == 0)
		{
			check_here(bash_boss, ptrcmd);
			care_redirect(&ptrcmd, &bash_boss);
			if (check_builtings(ptrcmd) == 0)
				child_exec(ptrcmd, bash_boss);
			else
				child_build(ptrcmd, bash_boss);
		}
		care_myprev(ptrcmd);
		ptrcmd = ptrcmd->next;
		i++;
	}
	wait_mypids(bash_boss);
	free_pids(bash_boss);
}
