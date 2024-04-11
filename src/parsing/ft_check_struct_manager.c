/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:33:05 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/11 09:21:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	*ft_create_token(char *token_line)
{
	int		i;
	char	*token;

	i = -1;
	token = ft_calloc(ft_strlen(token_line) + 1, sizeof(char));
	while (++i < ft_check_token_size(token_line))
	{
		token[i] = token_line[i];
	}
	token[i] = '\0';
	return (token);
}



char	*ft_path_handler(t_env *env, char *variable)
{
	int		index;
	char	*holder;

	if (env == NULL)
		return (NULL);
	index = ft_indexinenv(env, variable);
	if (index == -1)
		return (NULL);
	while (index--)
	{
		env = env->next;
	}
	holder = env->value;
	return (holder);
}

void	ft_check_variable_quotes_expansion(char *dest)
{
	int	i;

	i = -1;
	while (dest[++i])
	{
		if (dest[i] == '$' && dest[i + 1] == '\'')
		{
			ft_memmove(&dest[i], &dest[i + 1], ft_strlen(&dest[i + 1]) + 1);
		}
	}
}

void	ft_check_variable_expansion(char *src, char *dest, t_env *env)
{
	char	*token;
	char	*path;
	int		in_quotes;
	int		double_quote;
	char	*pid;
	char	*exit_status;

	double_quote = 0;
	in_quotes = 0;
	pid = ft_itoa(getpid());
	exit_status = ft_itoa(get_file_num()->bash->exit_status);
	while (*src)
	{
		if (*src == '\"' && ft_strchr(src, '$'))
			double_quote = !double_quote;
		if (*src == '\'' && !double_quote)
		{
			in_quotes = !in_quotes;
			*dest++ = *src++;
			continue ;
		}
		if (!in_quotes && *src == '$' && (*(src + 1) != '\''
				&& *(src + 1) != '\"'))
		{
			token = ft_create_token(src + 1);
			if (!ft_strcmp(token, "?"))
				path = exit_status;
			else if (!ft_strcmp(token, "$"))
				path = pid;
			else if (!*token)
				*dest++ = '$';
			else
				path = ft_path_handler(env, token);
			while (path != NULL && *path)
				*dest++ = *path++;
			src += ft_strlen(token) + 1;
			free(token);
		}
		else
			*dest++ = *src++;
	}
	free(pid);
	free(exit_status);
	*dest = '\0';
}

void	ft_extract_var(t_word_list *word_list, t_bash *bash)
{
	char	*dest;
	char	*word_cpy;
	int i =0;
	while (word_list)
	{
		if (ft_strcmp(word_list->word->word, "<<") == 0 && word_list->next)
		{
			if (word_list->next->word->tags == VARIABLE)
				word_list->next->word->tags = WORD;
		}
		if (word_list->word->tags == VARIABLE)
		{
			word_cpy = ft_calloc(10000 + 1, sizeof(char));
			dest = word_cpy;
			ft_check_variable_expansion(word_list->word->word, dest,
				bash->cpyenv);
			if (ft_strchr(word_cpy, '\''))
				ft_check_variable_quotes_expansion(dest);
			free(word_list->word->word);
			word_list->word->word = ft_strdup(word_cpy);
			free(word_cpy);
		}
		word_list = word_list->next;
	}
}
