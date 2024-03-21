/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:34:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 19:01:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	ft_space(char **line)
{
	while (**line == '2')
		(*line)++;
	return (1);
}

static void	ft_flag_update(char *flag_quotes, char line)
{
	if (*flag_quotes == 0 && (line == '\"' || line == '\''))
		*flag_quotes = line;
	else if (*flag_quotes == line)
		*flag_quotes = 0;
}

static void	ft_init_number(t_number *number)
{
	number->j = 0;
	number->flag_quotes = 0;
}

char	*ft_string_handle_2(char *line, char *modified_line)
{
	t_number	num;

	ft_init_number(&num);
	while (*line)
	{
		ft_flag_update(&num.flag_quotes, *line);
		if (num.flag_quotes == 0 && (*line == '<' || *line == '>'))
		{
			modified_line[num.j++] = '2';
			while (*line == '<' || *line == '>')
			{
				modified_line[num.j++] = *line;
				line++;
			}
			ft_space(&line);
			if (*line == '<' || *line == '>')
				return (NULL);
			modified_line[num.j++] = '2';
			num.flag_quotes = *line;
		}
		modified_line[num.j++] = *line;
		line++;
	}
	modified_line[num.j] = '\0';
	return (modified_line);
}
