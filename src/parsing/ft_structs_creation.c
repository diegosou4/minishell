/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:10:04 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 16:10:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_init_t_word_list(t_redir **redir_head, t_redir **current_redir)
{
	*redir_head = NULL;
	*current_redir = NULL;
}

t_redir	*ft_parse_redir_create(t_word_list *t_l)
{
	t_redir	*redir;
	t_redir	*redir_head;
	t_redir	*current_redir;

	ft_init_t_word_list(&redir_head, &current_redir);
	while (t_l)
	{
		if (t_l->word->tags == EXCECUTOR)
		{
			redir = ft_create_node();
			ft_init_redir_node(redir, t_l->next->word->word, t_l->word->flags);
			if (!redir_head)
			{
				redir_head = redir;
				current_redir = redir_head;
			}
			else
			{
				current_redir->next = redir;
				current_redir = current_redir->next;
			}
		}
		t_l = t_l->next;
	}
	return (redir_head);
}

t_cmd	*ft_parse_array(t_word_list *words_list)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		args_index;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = (char **)ft_calloc((10), sizeof(char *));
	redir = NULL;
	args_index = 0;
	while (words_list)
	{
		if (words_list->word->tags != EXCECUTOR
			&& words_list->word->tags != PATH)
		{
			cmd->args[args_index++] = (words_list->word->word);
		}
		if (!redir)
		{
			redir = ft_parse_redir_create(words_list);
			cmd->redir = redir;
		}
		words_list = words_list->next;
	}
	cmd->args[args_index] = NULL;
	return (cmd);
}

t_cmd	*ft_structure_creation(t_word_list **token_list)
{
	t_cmd	*new_cmd;
	t_cmd	*root;
	t_cmd	*current_cmd;
	int		i;

	new_cmd = NULL;
	if (!token_list)
		return (NULL);
	i = -1;
	while (token_list[++i])
	{
		new_cmd = ft_parse_array(token_list[i]);
		if (i == 0)
		{
			root = new_cmd;
			root->prev = NULL;
			current_cmd = root;
		}
		else
		{
			current_cmd->next = new_cmd;
			new_cmd->prev = current_cmd;
			current_cmd = current_cmd->next;
		}
	}
	return (root);
}
