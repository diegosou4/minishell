/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:42:12 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/16 16:35:52 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*buffer = NULL;
	char		*token_start;

	if (!str && !buffer)
		return (NULL);
	if (str)
		buffer = str;
	while (*buffer && ft_strchr(delimiters, *buffer))
		buffer++;
	token_start = buffer;
	buffer = ft_strpbrk(token_start, delimiters);
	if (buffer)
		*buffer++ = '\0';
	return (token_start);
}

int	ft_whitespace(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= '\b' && line[i] <= '\v') || line[i] == ' ')
	{
		i++;
	}
	if (i == (int)ft_strlen(line))
		return (0);
	return (1);
}

static	void	free_and_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_line_handler(t_line *line, t_env *cpyenv, int num)
{
	if (num == MAIN)
	{
		if (cpyenv == NULL)
			line->value_env = ft_strdup("non-env@user");
		else
			line->value_env = ft_duplineenv(cpyenv, "USER");
		if (line->value_env == NULL)
			line->value_env = ft_strdup("non-env@user");
		line->color_line = ft_strjoin(ANSI_COLOR_CYAN, (line->value_env));
		free_and_null(&line->value_env);
		line->line_text = ft_strjoin(line->color_line,
				"@🐧shell:$ " ANSI_COLOR_RESET);
		free_and_null(&line->color_line);
		line->line = readline(line->line_text);
		if (line->value_env != NULL)
			free(line->value_env);
		free_and_null(&line->line_text);
	}
	else if (num == HERE)
	{
		line->color_line = NULL;
		line->line_text = NULL;
		line->line = readline(A_C_P "🐧🐧heredoco> " ANSI_COLOR_RESET);
	}
}
