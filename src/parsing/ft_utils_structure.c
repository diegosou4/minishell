/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:42:12 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 15:42:12 by marvin           ###   ########.fr       */
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

//-----------------------------------Line Handler...........................

void	ft_line_handler(t_line *line, t_env *cpyenv)
{
	if (cpyenv == NULL)
		line->value_env = ("non-env@user");
	else
		line->value_env = ft_path_handler(cpyenv, "USER");
	line->color_line = ft_strjoin(ANSI_COLOR_CYAN, (line->value_env));
	line->line_text = ft_strjoin(line->color_line,
			"@🐧shell:$ " ANSI_COLOR_RESET);
	line->line = readline(line->line_text);
}