/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:49:22 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/05 12:49:26 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalphatwo(int c)
{
	if ((c >= 97 && c <= 122) || (c == 95) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c == 43) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

// Verifica se o char e um
// alfabeto
