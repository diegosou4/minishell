/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:50:07 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/05 13:50:08 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	size_s1 = ft_strlen((char *)s1);
	size_s2 = ft_strlen((char *)s2);
	new = (char *)malloc(((size_s1 + size_s2) + (1)) * sizeof(char));
	if (!new || (!s1 && !s2))
		return (0);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

/*
	The fuction strjoin return a new string with s1 and s2,
		so you need size of s1 and s2,
	before you neeed malloc,
		checks if malloc is done and if s1 and s2 have anything,
		if not return null,
	before you need two variables for copy s1 and s2,
		so in the final you put null in last and return the string
*/
