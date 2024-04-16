/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:34:08 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/15 14:30:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// static int	ft_space(char **line)
// {
// 	while (**line == '2')
// 		(*line)++;
// 	return (1);
// }

// static void	ft_flag_update(char *flag_quotes, char line)
// {
// 	if (line == '\"' || line == '\'')
// 	{
// 		*flag_quotes = !*flag_quotes;
// 	}
// 	else if (*flag_quotes == line)
// 		*flag_quotes = 0;
// }

static void	ft_init_number(t_number *number)
{
	number->i = 0;
	number->j = 0;
	number->flag_quotes = 0;
}

char	*ft_string_handle_2(char *line, char *modified_line)
{
	t_number	num;

	ft_init_number(&num);
	while (line[num.i])
	{
		if (line[num.i] == '\"' || line[num.i] == '\'')
		{
			num.flag_quotes = !num.flag_quotes;
			modified_line[num.j++] = line[num.i++];
		}
		else if (!num.flag_quotes && (line[num.i] == '<' || line[num.i] == '>'))
		{
			modified_line[num.j++] = '\2';
			modified_line[num.j++] = line[num.i];
			if (line[num.i + 1] == line[num.i])
				modified_line[num.j++] = line[++num.i];
			modified_line[num.j++] = '\2';
			num.i++;
		}
		else
			modified_line[num.j++] = line[num.i++];
	}
	modified_line[num.j] = '\0';
	return (modified_line);
}
