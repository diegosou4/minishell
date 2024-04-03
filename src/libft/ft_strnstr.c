/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:20:47 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/04 16:21:06 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	i = 0;
	if (*(char *)(little + k) == '\0')
		return ((char *)big);
	while (*(char *)(big + j) && i < len)
	{
		k = 0;
		while ((*(char *)(big + (j + k)) == *(char *)(little + k))
			&& *(char *)(little + k) != '\0')
		{
			if ((i + k) >= len)
				break ;
			k++;
		}
		if (*(char *)(little + k) == '\0')
			return ((char *)(big + j));
		j++;
		i++;
	}
	return (NULL);
}
