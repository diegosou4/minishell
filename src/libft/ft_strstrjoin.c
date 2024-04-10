/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrstrjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:57:33 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 13:57:34 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstrjoin(char *s1, char *s2, char s3, char *s4)
{
	char	*new_str;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	len += ft_strlen(s4) + 2;
	new_str = ft_calloc(len, sizeof(char));
	while (*s1 != '\0')
		new_str[j++] = *s1++;
	while (*s2 != '\0')
		new_str[j++] = *s2++;
	new_str[j++] = s3;
	while (*s4 != '\0')
		new_str[j++] = *s4++;
	return (new_str);
}
