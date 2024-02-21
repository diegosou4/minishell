/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:16:57 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/03 10:17:02 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	void	*p_s;

	p_s = s;
	while (size--)
	{
		*(unsigned char *)s++ = (unsigned char)c;
	}
	return (p_s);
}
