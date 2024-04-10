/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:15:09 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 20:15:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_free_wd_list_char(t_word_list **word_list, char *new_string)
{
	free(word_list);
	free(new_string);
}

void	ft_free_tokens_new_string(char **tokens, char *new_string)
{
	ft_free_double_pointers(tokens);
	free(new_string);
}

void	ft_free_line_env(t_line *line, t_env *cpyenv)
{
	if (line != NULL)
		ft_free_line_struct(line);
	if (cpyenv)
		ft_free_env_list(cpyenv);
}
