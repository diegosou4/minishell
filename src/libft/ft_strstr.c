/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:00:52 by diegmore          #+#    #+#             */
/*   Updated: 2023/09/06 20:14:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (&str[0]);
	while (str[i] != '\0')
	{
		j = 0;
		while ((str[i + j] == to_find[j] && to_find[j] != '\0'))
		{
			j++;
		}
		if (to_find[j] == '\0')
		{
			return (&str[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	array[];
	char	array1[];

        array[] = "";
        array1[] = "";
        printf("%s : ft_strstr \n", ft_strstr(array, array1));
        printf("%s : strstr \n", strstr(array,array1));
}
*/
