/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:33:05 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/11 09:27:40 by marvin           ###   ########.fr       */
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

static void ft_variable_help(t_number *num, char *src, char **dest, t_env *env)
{
	num->token = ft_create_token(src);
	if (!ft_strcmp(num->token, "?")) 
		num->path = num->exit_status; 
	else if (!ft_strcmp(num->token, "$")) 
		num->path = num->pid; 
	else if (!*num->token)
		**dest++ = '$';
	else
		num->path = ft_path_handler(env, num->token); 		
}
static void ft_num_init(t_number *num)
{
	num->path = NULL;
	num->double_quote = 0;
	num->in_quotes = 0;
	num->pid = ft_itoa(getpid());
	num->exit_status = ft_itoa(get_file_num()->bash->exit_status);

}
static void ft_num_free(t_number *num)
{
	free(num->pid);
	free(num->exit_status);
}
void	ft_check_variable_expansion(char *src, char *dest, t_env *env)
{
	t_number	num;

	ft_num_init(&num);
	while (*src)
	{
		if (*src == '\"' && ft_strchr(src, '$'))
			num.double_quote = !num.double_quote;
		if (*src == '\'' && !num.double_quote)
		{
			num.in_quotes = !num.in_quotes;
			*dest++ = *src++;
			continue ;
		}
		if (!num.in_quotes && *src == '$' && (*(src + 1) != '\''
				&& *(src + 1) != '\"'))
		{
			ft_variable_help(&num, src + 1, &dest, env);
			while (num.path != NULL && *num.path)
				*dest++ = *num.path++;
			src += ft_strlen(num.token) + 1;
			free(num.token);
		}
		else
			*dest++ = *src++;
	}
	ft_num_free(&num);
	*dest = '\0';
}

void	ft_extract_var(t_word_list *word_list, t_bash *bash)
{
	char	*dest;
	char	*word_cpy;

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
