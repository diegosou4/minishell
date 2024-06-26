/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:59:24 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 11:13:51 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_boolstrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_charcmp(char c, char s)
{
	if (c == s)
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	length_s;

	length_s = ft_strlen((char *)str);
	i = 0;
	while (i < length_s)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)c)
	{
		return ((char *)(str + length_s));
	}
	else
	{
		return (NULL);
	}
}
