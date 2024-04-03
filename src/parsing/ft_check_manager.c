/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:07:06 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/03 16:00:56 by marvin           ###   ########.fr       */
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

int	ft_lexer_analysis(t_word_list *words_list, t_bash *bash, char *new_string)
{
	ft_extract_var(words_list, bash);
	ft_flags_tags_assignment(words_list);
	if (ft_check_words_list(words_list) == 1)
		words_list->redirection = TRUE;
	else
		words_list->redirection = FALSE;
	if (ft_check_valid_redir(words_list) == 0)
	{
		free(new_string);
		return (0);
	}
	ft_quotes_remove(words_list);
	return (1);
}

int	ft_check_words_list(t_word_list *tokens)
{
	while (tokens)
	{
		if (tokens->word->tags == EXCECUTOR)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

static int	ft_special_pipe_case(char *line)
{
	if (line[0] == '|' && line[1] == '|')
	{
		printf("syntax error near `||' More than one pipe found! 🚰🐟\n");
		return (0);
	}
	return (1);
}

static int	ft_whitespace_1(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= '\b' && line[i] <= '\v') || line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		printf("syntax error near `|' (no args) 🚰🙊\n");
		return (0);
	}
	else if (line[i] == '|')
	{
		printf("syntax error near `||' More than one pipe found! 🚰🐟\n");
		return (0);
	}
	return (1);
}

static int	ft_check_pipes(char *line)
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
		if (flag == 0 && (line[i] == '|') && (line[i + 1] == '\0' || line[i + 1] == '|' || line[i + 1] == ' '))
		{
			if (line[i + 1] == '\0')
			{
				printf("syntax error near `|' (no args) 🚰🙊\n");
				return (0);
			}
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
	{
		printf("-🚫 bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else if (ft_strcmp(line[i - 1], "<") == 0 || ft_strcmp(line[i - 1], ">") == 0)
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
	if (!ft_check_pipes(line))
	{
		ft_free_double_pointers(split_line);
		bash->exit_status = 2;
		return (0);
	}
	ft_free_double_pointers(split_line);
	return (1);
}
