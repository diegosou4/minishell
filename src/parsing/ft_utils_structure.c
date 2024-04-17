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
