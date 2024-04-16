/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseredir_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:20:51 by juan-pma          #+#    #+#             */
/*   Updated: 2024/04/16 19:22:00 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	caseptr(char first, char second)
{
	if (first == '>' && second == '>')
		return (append_out);
	else if (first == '<' && second == '<')
		return (here_doc);
	else if (first == '<' && second == '>')
		return (inandout);
	else if (first == '<' && (second != '>' || second != '<'))
		return (redir_in);
	else if (first == '>' && (second != '>' || second != '<'))
		return (redir_out);
	return (0);
}

char	*ft_parse_redir(char *str)
{
	char	*ptr;
	char	*new;
	int		j;
	int		i;
	int		case_num;

	j = 0;
	i = 0;
	ptr = str;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (ptr[j])
	{
		case_num = caseptr(ptr[j], ptr[j + 1]);
		if (case_num == 0)
			new[i] = ptr[j];
		else if (case_num != 0)
			new[i] = case_num;
		if (case_num >= 3 && case_num <= 5)
		{
			j++;
		}
		i++;
		j++;
	}
	return (new);
}

char	*cleantoken(char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j++;
		i++;
	}
	len = (i - j);
	newstr = (char *)ft_calloc(sizeof(char), len);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		newstr[j] = str[i];
		j++;
		i++;
	}
	return (newstr);
}
