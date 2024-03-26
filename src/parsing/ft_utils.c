/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:21:34 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 15:46:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/*
    🚩 check this function as we are alocating
    memmory here.
*/

char	*ft_strcpy(char *dest, const char *src);

char	*ft_strcpy(char *dest, const char *src)
{
	if (!src)
		return (NULL);
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

// This line is to move the string one infront
//and remove the $ when is followed by a '

// static void	ft_preline(char *line)
// {
// 	int	i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] == '$' && line[i + 1] == '\'')
// 		{
// 			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
// 		}
// 	}
// }

void	ft_checker_double_single(char *str, char quote)
{
	char	*src;
	char	*dest;
	int		flag;

	flag = 0;
	src = str;
	dest = str;
	while (*src)
	{
		if (*src == quote && !flag)
		{
			src++;
			continue ;
		}
		if (*src == quote && flag)
			flag = !flag;
		*dest++ = *src++;
	}
	*dest = '\0';
}

void	ft_checker_quotes(char *str)
{
	char	*src;
	int		flag;

	flag = 0;
	src = str;
	while (*src)
	{
		if (*src == '\'' && !flag)
		{
			ft_checker_double_single(src, '\'');
			flag = !flag;
		}
		else if (*src == '\"' && !flag)
		{
			ft_checker_double_single(src, '\"');
			flag = !flag;
		}
		src++;
	}
}

void	ft_quotes_remove(t_word_list *word_list)
{
	char	*word;

	while (word_list)
	{
		word = word_list->word->word;
		ft_checker_quotes(word);
		word_list = word_list->next;
	}
}
