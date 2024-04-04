/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:13:49 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/04 12:32:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_line	*ft_init_manager(t_line *line)
{
	line->line = NULL;
	line->color_line = NULL;
	line->usr = NULL;
	line->line_text = NULL;
	return (line);
}

void	ft_bash_boss_init(t_bash *bash, char **env)
{
	bash->pid = NULL;
	bash->env = ft_arrcpy(env);
	bash->cpyenv = ft_nenv(env, 1);
	bash->commands = NULL;
	bash->in = 0;
	bash->out = 0;
	bash->fdin = 0;
	bash->fdout = 0;
	bash->pipein = 0;
	bash->pipeout = 0;
	bash->exit_status = 0;
	bash->line = NULL;
}
