/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:33:05 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/28 17:33:07 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int ft_lstsize_(t_word_list *lst)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_word_list *ft_lstlast_(t_word_list *lst)
{
	int tamlist;
	int i;

	i = 0;
	tamlist = ft_lstsize_(lst);
	while (i < tamlist - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}
int ft_extract_var(t_word_list *word_list, char **env)
{
	char *token;
	char *appear;
	char *path;
	int len;

	path = ft_calloc(100, sizeof(char *));
	while (word_list)
	{
		appear = ft_strchr((const char *)word_list->word->word, '$');

		if (appear)
		{
			appear++;
			token = ft_strtok(appear, " ");
			if (ft_strchr(token, '\''))
			{
				len = ft_strlen(token);
				token[len - 1] = '\0';
				ft_memmove(token, token, len - 2);
			}
			path = ft_getenv(env, token, TRUE);
			word_list->word->word = path;
		}
		word_list = word_list->next;
	}

	return (1);
}
