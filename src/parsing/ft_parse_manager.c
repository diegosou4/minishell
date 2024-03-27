/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:42:35 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 20:13:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// Define a global flag to indicate if the prompt has been printed
/*
	This function will create an array
	of structures, that will contain all the
	tokens already Trimmed.

	1. Args = the comand line.
	2. Output a list of tokens, to create

*/

t_tags	ft_tags(t_word_desc *word)
{
	char	*word_cpy;
	int		len;

	word_cpy = word->word;
	len = ft_strlen(word_cpy);
	if (word->flags == 1 || word->flags == 2
		|| word->flags == 3 || word->flags == 4)
	{
		return (EXCECUTOR);
	}
	else if ((word_cpy[0] == '\'' && word_cpy[len - 1] == '\''))
		return (WORD);
	else if (ft_strcmp(word->word, "$") == 0)
		return (WORD);
	else if (ft_strcmp(word_cpy, "$?") == 0)
		return (SPECIAL_VAR);
	else if (ft_strchr(word->word, '$'))
		return (VARIABLE);
	else
		return (WORD);
}

int	ft_flag(char *word)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(word, ">>") == 0)
		flag = append_out;
	else if (ft_strcmp(word, "<<") == 0)
		flag = here_doc;
	else if (ft_strcmp(word, "<") == 0)
		flag = redir_in;
	else if (ft_strcmp(word, ">") == 0)
		flag = redir_out;
	else if (ft_strcmp(word, "<>") == 0)
		flag = inandout;
	return (flag);
}

t_word_desc	*ft_cte_wd_d(char *word, int flag)
{
	t_word_desc	*new_word;

	new_word = ft_calloc(1, sizeof(t_word_desc));
	new_word->word = ft_strdup(word);
	new_word->flags = flag;
	new_word->tags = ft_tags(new_word);
	return (new_word);
}

t_word_list	*create_word_node(t_word_desc *word)
{
	t_word_list	*new_node;

	new_node = malloc(sizeof(t_word_list));
	new_node->word = word;
	new_node->next = NULL;
	return (new_node);
}
t_word_lists	*ft_init_word_lista(char *token)
{
	t_word_lists *word_lists;

	word_lists = ft_calloc(1, sizeof(t_word_lists));
	word_lists->current_token = NULL;
	word_lists->node = NULL;
	word_lists->head = NULL;
	word_lists->subtoken = ft_strtok(token, "2");
	return (word_lists);
}

t_word_list	*tokenize_and_print(char *token)
{
	t_word_lists	*wls;
	t_word_list		*head;

	if (!token || !token[0])
		return (NULL);
	wls = ft_init_word_lista(token);
	while (wls->subtoken != NULL)
	{
		if (wls->subtoken[0] != '\0')
		{
			wls->word_desc = ft_cte_wd_d(wls->subtoken, ft_flag(wls->subtoken));
			wls->node = create_word_node(wls->word_desc);
			if (wls->head == NULL)
			{
				wls->head = wls->node;
				wls->current_token = wls->node;
			}
			else
			{
				wls->current_token->next = wls->node;
				wls->current_token = wls->node;
			}
		}
		wls->subtoken = ft_strtok(NULL, "2");
	}
	head = wls->head;
	free(wls->subtoken);
	free(wls);
	return (head);
}
