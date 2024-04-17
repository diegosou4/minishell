/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:07:06 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/16 11:19:09 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_special_pipe_case(char *line)
{
	if (line[0] == '|' && line[1] == '|')
	{
		return (error_syntax
			("syntax error near `||' More than one pipe found! 🚰🐟\n", 0));
	}
	return (1);
}

int	ft_whitespace_1(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= '\b' && line[i] <= '\v') || line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return (error_syntax("syntax error near `|' (no args) 🚰🙊\n", 0));
	}
	else if (line[i] == '|')
	{
		return (error_syntax
			("syntax error near `||' More than one pipe found! 🚰🐟\n", 0));
	}
	return (1);
}

int	ft_check_pipes(char *line)
{
	int		i;
	char	flag;

	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (flag == 0 && (line[i] == '\"' || line[i] == '\''))
			flag = line[i];
		else if (flag == line[i])
			flag = 0;
		if (flag == 0 && ft_special_pipe_case(&line[i]) == 0)
			return (0);
		if (flag == 0 && (line[i] == '|') && (line[i + 1] == '\0'
				|| line[i + 1] == '|' || line[i + 1] == ' '))
		{
			if (line[i + 1] == '\0')
				return (error_syntax("syntax error near `|' (no args) 🚰🙊\n",
						0));
			else if (line[i + 1] == ' ' && !ft_whitespace_1(&line[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_directions(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		;
	if (ft_strcmp(line[i - 1], "<<") == 0 || ft_strcmp(line[i - 1], ">>") == 0)
		return (error_syntax
			("-🚫 bash: syntax error near unexpected token `newline'\n", 0));
	else if (ft_strcmp(line[i - 1], "<") == 0 
		|| ft_strcmp(line[i - 1], ">") == 0)
		return (error_syntax
			("-🚫 bash: syntax error near unexpected token `newline'\n", 0));
	return (1);
}
