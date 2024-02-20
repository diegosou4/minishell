/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:45:25 by diegmore          #+#    #+#             */
/*   Updated: 2023/10/10 16:45:27 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwordls(unsigned int n)
{
	int	wordls;

	wordls = 0;
	if (n == 0)
		wordls++;
	while (n != 0)
	{
		n = n / 10;
		wordls++;
	}
	return (wordls);
}

static char	*ft_putintchar(unsigned int n, char *str, size_t len, int negative)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		str[0] = '0';
	}
	while (n != 0)
	{
		i = n % 10;
		str[len] = i + '0';
		n = n / 10;
		len--;
	}
	if (negative == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len_str;
	int				negative;
	unsigned int	num;

	num = n;
	len_str = 0;
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		len_str = 1;
		num *= -1;
	}
	len_str += (ft_countwordls(num) + 1);
	str = (char *)ft_calloc(len_str, sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_putintchar(num, str, (len_str - 2), negative);
	return (str);
}
