/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:38:09 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/06 16:03:59 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (*(unsigned char *)(str1
			+ i) == *(unsigned char *)(str2 + i)))
	{
		i++;
	}
	return ((*(const unsigned char *)(str1 + i) - *(const unsigned char *)(str2
		+ i)));
}
