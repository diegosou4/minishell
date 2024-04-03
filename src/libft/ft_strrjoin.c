/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 11:06:56 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strrjoin(char **arr, char *str)
{
	char **newstr;
	int i;

	i = len_darray(arr) + 2;

	newstr = ft_calloc(sizeof(char *), i);

	int j;
	j = 0;
	while (j != (i - 3))
	{
		newstr[j] = ft_strdup(arr[j]);
		j++;
	}
	i = j;
	newstr[j++] = ft_strdup(str);
	newstr[j++] = ft_strdup(arr[i]);
	freedouble_malloc(arr, len_darray(arr));
	return (newstr);
}