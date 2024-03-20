/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:07:06 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/20 12:07:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/*
    This function checks for double pipes in the parsed input line.
    It iterates through the array of strings representing the line and
    checks if two consecutive strings are both pipes or if a pipe is
    followed by a NULL string, indicating a void character after the pipe.

    Arguments:
        - line: Array of strings representing the parsed input line.
        - operations: Structure containing information about operations.

    Returns:
        - 1 if no double pipes are found, indicating success.
        - 0 if double pipes are found or a pipe is followed by a void character.
*/

static	int	ft_special_pipe_case(char *line)
{
	int	i;

	i = -1;
	if (line[0] == '|' && line[1] == '|')
	{
		printf("syntax error near `||' More than one pipe found! 🚰🐟\n");
		return (0);
	}
	return (1);
}

static	int	ft_check_pipes(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (ft_special_pipe_case(line[i]) == 0)
			return (0);
		if (strcmp(line[i], "|") == 0
			&& (line[i + 1] == NULL || strcmp(line[i + 1], "|") == 0))
		{
			if (line[i + 1] == NULL)
				printf("syntax error near `|' (no args) 🚰🙊\n");
			else
				printf("syntax error near `||' More than one pipe found! 🚰🐟\n");
			return (0);
		}
		i++;
	}
	if (line[i - 1][ft_strlen(line[i - 1]) - 1] == '|')
	{
		printf("syntax error near `|' (no args) 🚰🙊\n");
		return (0);
	}
	return (1);
}

static	int	ft_check_directions(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		;
	if (ft_strcmp(line[i - 1], "<<") == 0 || ft_strcmp(line[i - 1], ">>") == 0)
	{
		printf("-🚫 bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else if (ft_strcmp(line[i - 1], "<") == 0
		|| ft_strcmp(line[i - 1], ">") == 0)
	{
		printf("-🚫 bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
/*

    This funciton will check the input as is given by the user,
    without any pretreatement, in order to find error before creating any
    structure.

*/

int	ft_check_input(char *line, t_bash *bash)
{
	char	**split_line;

	bash->exit_status = 0;
	if (!line)
		return (0);
	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0])
	{
		free(split_line);
		return (0);
	}
	if (!ft_check_pipes(split_line)
		|| !ft_check_redir_pipes(split_line)
		|| !ft_check_directions(split_line))
	{
		ft_free_double_pointers(split_line);
		bash->exit_status = 2;
		return (0);
	}
	ft_free_double_pointers(split_line);
	return (1);
}
