/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:42:35 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/17 16:53:11 by diegmore         ###   ########.fr       */
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
	if (word->flags == 1 || word->flags == 2 || word->flags == 3
		|| word->flags == 4)
	{
		return (EXCECUTOR);
	}
	else if ((word_cpy[0] == '\'' && word_cpy[len - 1] == '\''))
		return (WORD);
	else if (ft_strcmp(word->word, "$") == 0)
		return (WORD);
	else if (ft_strcmp(word_cpy, "$?") == 0)
		return (VARIABLE);
	else if (ft_strchr(word->word, '$'))
		return (VARIABLE);
	else
		return (WORD);
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

static void	help_token(t_word_lists *wls)
{
	if (wls->subtoken[0] != '\0')
	{
		wls->word_desc = ft_cte_wd_d((wls->subtoken), ft_flag(wls->subtoken));
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
		help_token(wls);
		wls->subtoken = ft_strtok(NULL, "\2");
	}
	head = wls->head;
	if (wls->subtoken != NULL)
		free(wls->subtoken);
	if (wls != NULL)
		free(wls);
	return (head);
}
