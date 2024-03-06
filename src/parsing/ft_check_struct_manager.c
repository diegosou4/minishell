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
	while (token_line[i] != '\0' && ((ft_isalnum(token_line[i]) 
			|| ft_isdigit(token_line[i]) || ft_isalnum(token_line[i]) 
			|| token_line[i] == '_')))
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

	
	if(env == NULL)
		return(NULL);
	index = ft_indexinenv(env, variable);
	if (index == -1)
		return NULL;
	while (index--)
	{
		env = env->next;
	}
	holder = ft_calloc(ft_strlen(env->value + 1), sizeof(char ));
	holder = env->value + 1;
	return (holder);
}
void ft_check_variable_quotes_expansion(char *dest)
{
	int i;
	i = -1;
	while(dest[++i])
	{
		if (dest[i] == '$' && dest[i + 1] == '\'')
		{
			ft_memmove(&dest[i], &dest[i + 1], ft_strlen(&dest[i + 1]) + 1);
			// ft_checker_quotes(&line[i], 2);
		}
	}
	printf("line without $ :%s:\n", dest);
}
void ft_check_variable_expansion(char *src, char *dest, t_env *env)
{
	char *token;
	char *path;
	int in_quotes;
	int double_quote;

	double_quote = 0;
	in_quotes = 0;
	while (*src)
	{
		if (*src == '\"' && ft_strchr(src, '$'))
			double_quote = !double_quote;
		if (*src == '\'' && !double_quote)
        {
            in_quotes = !in_quotes; // Toggle the quotes flag
            *dest++ = *src++;
            continue; // Skip to the next character
        }
		if (!in_quotes && *src == '$' && (*(src + 1) != '\'' && *(src + 1) != '\"'))
		{
			token = ft_create_token(src + 1);
			printf("this is the toke :%s:\n", token);
			path = ft_path_handler(env, token);
			while (path != NULL && *path)
				*dest++ = *path++;
			src += ft_strlen(token) + 1;
			free(token);
		}
		else
			*dest++ = *src++;
		
	}
	*dest = '\0';
}

int ft_extract_var(t_word_list *word_list, t_env *env)
{
	char *token;
	char *src;
	char *dest;
	char *path;
	char *word_cpy;

	while (word_list)
	{
		if (word_list->word->tags == VARIABLE)
		{
			word_cpy = ft_calloc(10000 + 1, sizeof(char));
			src = word_list->word->word;
			dest = word_cpy;
			ft_check_variable_expansion(src, dest, env);
			if (ft_strchr(word_cpy, '\''))
				ft_check_variable_quotes_expansion(dest);
			word_list->word->word = word_cpy;
		}
		word_list = word_list->next;
	}
	return (1);
}
