/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:21:41 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 11:23:49 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

t_word_lists	*ft_init_word_lista(char *token)
{
	t_word_lists	*word_lists;

	word_lists = ft_calloc(1, sizeof(t_word_lists));
	word_lists->current_token = NULL;
	word_lists->node = NULL;
	word_lists->head = NULL;
	word_lists->subtoken = ft_strtok(token, "\2");
	return (word_lists);
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
