/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:22:54 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/20 12:24:14 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	ft_index(t_env *env, char *this)
{
	int		index;
	t_env	*ptr;

	index = 0;
	ptr = env;
	if (env == NULL)
		return (-1);
	if (ft_strlen(this) == 0)
		return (-1);
	while (ptr != NULL)
	{
		if ((ft_strncmp(ptr->key, this, ft_strlen(this)) == 0) 
			&& (ft_strlen(ptr->key) == ft_strlen(this) + 1))
		{
			return (index);
		}
		ptr = ptr->next;
		index++;
	}
	return (-1);
}

char	*ft_path_handler(t_env *env, char *variable)
{
	int		index;
	char	*holder;

	if (env == NULL)
		return (NULL);
	index = ft_index(env, variable);
	if (index == -1)
		return (NULL);
	while (index--)
	{
		env = env->next;
	}
	holder = env->value;
	return (holder);
}

void	ft_variable_help(t_number *num, char *src, t_env *env)
{
	num->token = ft_create_token(src);
	if (!ft_strcmp(num->token, "?")) 
		num->path = num->exit_status; 
	else if (!ft_strcmp(num->token, "$")) 
		num->path = num->pid; 
	else if (num->token[0] == '\0')
		num->path = (num->dolar);
	else
		num->path = (ft_path_handler(env, num->token)); 
}

int	ft_check_variable_helper(char **dest, char **src, t_number *num)
{
	while (**src == '\'')
		**dest++ = **src++;
	if (**src == '\'' && !num->double_quote)
	{
		num->in_quotes = !num->in_quotes;
		return (1);
	}
	return (0);
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
