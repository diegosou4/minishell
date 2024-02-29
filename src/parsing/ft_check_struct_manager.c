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
static int ft_check_token_size(char *token_line)
{
	int i;
	
	i = 0;
	while (token_line[i] != '\0' && ((ft_isalnum(token_line[i]) || ft_isdigit(token_line[i]) || ft_isalnum(token_line[i]) || token_line[i] == '_')))
		i++;
	return (i);
}
static char *ft_create_token(char *token_line)
{
	int i;
	char *token;

	i = -1;
	token = ft_calloc(ft_strlen(token_line), sizeof(char));
	while (++i < ft_check_token_size(token_line))
	{
		token[i] = token_line[i];
	}
	return (token);
}
char *ft_path_handler(t_env *env, char *variable)
{
	int index;
	char *holder;

	printf("VARIABLE :%s:\n", variable);
	index = ft_indexinenv(env, variable);
	if (index == -1)
		return NULL;
	while (index--)
	{
		env = env->next;
	}
	printf("key    :%s:\n", env->key);
	printf("value  :%s:\n", env->value);
	printf(":%d:\n", index);
	holder = env->value + 1;
	return (holder);
}
int ft_extract_var(t_word_list *word_list, t_env *env)
{
	char *token;
	char *appear;
	char *path;
	int len;
	char *buffer;
	int i;
	char *new_path;
	char *new_token;

	i = 0;
	path = ft_calloc(1000, sizeof(char *));
	buffer = ft_calloc((ft_strlen(word_list->word->word)), sizeof(char *));
	char *word_cpy;

	while (word_list)
	{
		if (word_list->word->tags == SPECIAL_VAR ||
			word_list->word->tags == VARIABLE)
		{
			// ft_checker_quotes(word_list->word->word);
			while (word_list->word->word[i] != '$' && word_list->word->word[i])
				i++;
			word_cpy = ft_calloc(i + 1, sizeof(char));
			ft_strlcat(word_cpy, word_list->word->word, i + 1);
			// printf("WORD ------------> :%s:\n", word_list->word->word);
			// printf("BUFF ------------> :%s:\n", word_cpy);
			appear = ft_strchr((const char *)word_list->word->word, '$');
			if (appear)
			{
				appear++;
				i++;
				token = ft_create_token(appear);
				// printf("TOKEN ---------> :%s:\n", token);
				len = ft_strlen(token);
				path = ft_path_handler(env, token);
				if (path)
					new_path = ft_strjoin(word_cpy, path);
				else
				{
					new_path = word_cpy;
					word_list->word->word = new_path;
					return (1);
				}
				// printf("BUFF ---------> :%s:\n", new_path);
				i += len;				
				new_token = ft_strjoin(new_path, &word_list->word->word[i]);
				// printf("NEW TOKEN ---------> :%s:\n", new_token);
				word_list->word->word = new_token;
			}
		}
		word_list = word_list->next;
	}
	return (1);
}
