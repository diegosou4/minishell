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

static int	ft_space(char *line, t_number *num)
{
	int	i;

	i = num->i + 1;
	while (line[i] == '\2')
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		return (0);
	}
	return (1);
}

static void	ft_init_number(t_number *number)
{
	number->i = 0;
	number->j = 0;
	number->flag_quotes = 0;
}

static void	ft_handler_2_help(char *line, char *modified_line, t_number *num)
{
	num->flag_quotes = !num->flag_quotes;
	modified_line[num->j++] = line[num->i++];
}

char	*ft_string_handle_2(char *line, char *modified_line)
{
	t_number	num;

	ft_init_number(&num);
	while (line[num.i])
	{
		if (line[num.i] == '\"' || line[num.i] == '\'')
			ft_handler_2_help(line, modified_line, &num);
		else if (!num.flag_quotes && (line[num.i] == '<' || line[num.i] == '>'))
		{
			modified_line[num.j++] = '\2';
			modified_line[num.j++] = line[num.i];
			if (line[num.i + 1] == line[num.i])
				modified_line[num.j++] = line[++num.i];
			if (!ft_space(line, (&num)))
				return (NULL);
			modified_line[num.j++] = '\2';
			num.i++;
		}
		else
			modified_line[num.j++] = line[num.i++];
	}
	modified_line[num.j] = '\0';
	return (modified_line);
}
