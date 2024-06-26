/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:43:10 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 11:14:24 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char *s, char sep)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] != sep && s[i])
		{
			words++;
			i++;
		}
		while (s[i] != sep && s[i])
			i++;
	}
	return (words);
}

static int	ft_numberchar(char *s, char sep)
{
	int	i;
	int	numberchar;

	numberchar = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		while (s[i] != sep && s[i])
		{
			i++;
			numberchar++;
		}
		if (s[i] == sep)
			return (numberchar);
	}
	return (numberchar);
}

static int	ft_givestring(char *s, char sep, char *dest, char n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		while (s[i] != sep && s[i])
		{
			dest[j] = s[i];
			i++;
			j++;
		}
		dest[j] = n;
		if (s[i] == sep)
			return (i);
	}
	return (i);
}

void	*freedouble_malloc(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		s[i] = NULL;
		i--;
	}
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

char	**mysplit(char const *s, char c, char n)
{
	char	**str;
	int		i;
	int		k;
	int		p;

	if (!s)
		return (0);
	p = 0;
	k = 0;
	i = 0;
	str = (char **)ft_calloc((ft_countwords((char *)s, c) + 1), sizeof(char *));
	if (!str)
		return (0);
	while (i < ft_countwords((char *)s, c))
	{
		str[i] = (char *)ft_calloc((ft_numberchar((char *)(s + p), c) + 2),
				sizeof(char));
		if (!str[i])
			return (freedouble_malloc(str, i - 1));
		k = ft_givestring((char *)(s + p), c, str[i], n);
		p = p + k;
		i++;
	}
	return (str);
}
