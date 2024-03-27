/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:49:17 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/05 13:49:20 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (*(const unsigned char *)(s1
			+ i) == *(const unsigned char *)(s2 + i))
		&& *(const unsigned char *)(s1 + i) && *(const unsigned char *)(s2 + i))
	{
		i++;
	}
	return ((*(const unsigned char *)(s1 + i) 
		-*(const unsigned char *)(s2 + i)));
}
