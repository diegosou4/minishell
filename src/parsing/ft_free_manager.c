/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:14:31 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/09 13:01:36 by marvin           ###   ########.fr       */
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
	if (split_line)
	{
		free(split_line);
		split_line = NULL;
	}
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
		if(temp->key != NULL)
			free(temp->key);
		if(temp->value != NULL)
			free(temp->value);
		free(temp);
	}
}

void	ft_free_line_struct(t_line *line)
{
	if (line->line_text)
		free(line->line_text);
	if (line->color_line)
		free(line->color_line);
	// if(line->value_env)
	// 	free(line->value_env);
	// if(line->usr)
	// 	free(line->usr);
	if (line->line)
		free(line->line);

}

void	ft_free_exit_status(t_line *line, t_env *cpyenv, char **env)
{
	if (line || cpyenv)
	{
		ft_free_line_env(line, cpyenv);
		line = NULL;
		cpyenv = NULL;
	}
	//write(1, "(exit)\n", 7);
	//printf("%i",ft_atoi(ft_itoa(g_exit_status)));
	if (env != NULL)
	{
		ft_free_double_pointers(env);
		env = NULL;
	}
}

