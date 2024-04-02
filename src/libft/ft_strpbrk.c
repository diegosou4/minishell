/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:14:35 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 09:14:05 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
NAME
       strpbrk - search a string for any of a set of bytes

SYNOPSIS
       #include <string.h>

       char *strpbrk(const char *s, const char *accept);

DESCRIPTION
       The strpbrk() function locates the first occurrence in the string s of any
       of the bytes in the string accept.
*/

char	*ft_strpbrk(const char *str, const char *charset)
{
	const char	*s;
	const char	*c;

	s = str;
	while (*s != '\0')
	{
		c = charset;
		while (*c != '\0')
		{
			if (*s == *c)
			{
				return ((char *)s);
			}
			c++;
		}
		s++;
	}
	return (NULL);
}
