/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/14 17:33:06 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ft_getenv(char **env, char *str, t_bool i)
{
	char	*p;

	p = NULL;
	while (*env != NULL)
	{
		p = ft_strnstr(*env, str, ft_strlen(str));
		if (i == TRUE)
		{
		if (p != NULL)
			return (p + 5);
		}
		else 
		{
			
		if (p != NULL)
			return (p + 4);
		}
		env++;
	}
	return (NULL);
}




