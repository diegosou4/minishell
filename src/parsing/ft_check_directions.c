/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_directions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:44:43 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/15 14:33:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// This function checks for syntax errors related to redirection symbols
// (>, <) and specific combinations of redirection symbols
// and subsequent arguments.
// It counts the number of redirection symbols encountered
//in the parsed input line,
// ensuring that no more than two redirection symbols are present.
// Arguments:
// - line: Array of strings representing the parsed input line.
// - operations: Structure containing information about operations.
// Returns:
// - 1 if no syntax errors are found, indicating success.
// - 0 if a syntax error is detected.
// Helper function to print syntax error message

static void	ft_print_syntax_error(void)
{
	printf("dir 🚫 in-bash: syntax error near unexpected token `\n");
}

static int	ft_has_valid_redir_flag(t_word_desc *word)
{
	char	first_char;
	int		flag;

	first_char = word->word[0];
	flag = word->flags;
	if (first_char == '>' && (flag == 1 || flag == 4))
		return (1);
	else if (first_char == '<' && (flag == 2 || flag == 3 || flag == 5))
		return (1);
	else
		return (0);
}

int	ft_check_valid_redir(t_word_list *word_list)
{
	int	i;

	i = 0;
	while (word_list->next)
	{
		if (word_list->word->word[0] == '\''
			|| word_list->word->word[0] == '\"')
			 i = 0;
		else if (word_list->word->word[i] == '>' || word_list->word->word[i] == '<')
		{
			if (!ft_has_valid_redir_flag(word_list->word))
			{
				ft_print_syntax_error();
				return (0);
			}
		}
		word_list = word_list->next;
	}
	if (word_list->word->word[i] == '<' || word_list->word->word[i] == '>')
	{
		printf("-direction🚫 on-bash: syntax error near unexpected token `\n");
		return (0);
	}
	return (1);
}

int	ft_check_redir_pipes(char **line)
{
	int	i;

	i = -1;
	if (!line || !*line)
		return (0);
	while (line[++i] && line[i + 1])
	{
		if ((ft_strcmp(line[i], "<<") == 0 || ft_strcmp(line[i], ">>") == 0)
			&& ft_strcmp(line[i + 1], "|") == 0)
		{
			printf("parse error near `|' 🚫. \n");
			return (0);
		}
		else if ((ft_strcmp(line[i], ">") == 0 || ft_strcmp(line[i], "<") == 0)
			&& ft_strcmp(line[i + 1], "|") == 0)
		{
			printf("parse error near `|' 🚫.\n");
			return (0);
		}
	}
	return (1);
}
