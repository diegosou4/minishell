/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:14:31 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 20:15:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_free_double_pointers(char **split_line)
{
	int	i;

	i = -1;
	if (split_line == NULL)
		return ;
	while (split_line[++i])
	{
		free(split_line[i]);
		split_line[i] = NULL;
	}
	free(split_line);
}

void	ft_free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*temp;

	current = env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp);
	}
}

void	ft_free_line_struct(t_line *line)
{
	free(line->line_text);
	free(line->color_line);
	free(line->line);
}

void	ft_free_exit_status(t_line *line, t_env *cpyenv, char **env)
{
//	ft_free_line_env(line, cpyenv);
	write(1, "(exit)\n", 7);
	ft_free_double_pointers(env);
}

