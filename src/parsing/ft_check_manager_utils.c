/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_manager_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:54:18 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/16 20:54:20 by juan-pma         ###   ########.fr       */
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
	if (ft_charcmp(split_line[0][0], 124) == 1)
	{
		ft_free_double_pointers(split_line);
		bash->exit_status = 127;
		return (error_syntax("syntax error near `|' (no args) 🚰🙊\n", 0));
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
