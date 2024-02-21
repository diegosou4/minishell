/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:57:20 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/11 19:23:19 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		while (n--)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
// a funcao recebe a mesma string entao
// ela verifica se o dest esta a frente na memoria
// caso esteja ele faz de tras para frente
// para evitar sobreposicao de memoria
