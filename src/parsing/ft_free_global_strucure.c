/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_global_strucure.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:12:48 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 20:12:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_free_list_tokens(t_word_list **word_list, char **tokens,
		char *new_string, t_bash *bash)
{
	if (bash)
		bash->exit_status = 2;
	if (new_string)
		ft_free_wd_list_char(word_list, new_string);
	else
		ft_free_double_word_list(word_list);
	ft_free_double_pointers(tokens);
}

void	ft_free_t_word_list(t_word_list *word_list)
{
	t_word_list	*temp;

	while (word_list)
	{
		temp = word_list;
		word_list = word_list->next;
		free(temp->word->word);
		free(temp->word);
		free(temp);
	}
	free(word_list);
}

void	ft_free_double_word_list(t_word_list **word_desc)
{
	int	i;

	i = -1;
	while (word_desc[++i])
	{
		ft_free_t_word_list(word_desc[i]);
	}
	free(word_desc);
}

void	ft_free_redir_list(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp);
	}
}

void	ft_free_cmd_structure(t_cmd *cmd_structure)
{
	t_cmd	*temp;

	while (cmd_structure)
	{
		temp = cmd_structure->next;
		free(cmd_structure->path);
		free(cmd_structure->args);
		ft_free_redir_list(cmd_structure->redir);
		free(cmd_structure);
		cmd_structure = temp;
	}
}
