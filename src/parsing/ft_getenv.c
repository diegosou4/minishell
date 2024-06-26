/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 16:31:09 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ft_getenv(char **env, char *str, int i)
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
			env++;
		}
	}
	return (NULL);
}

char	*ft_getpath(char **env)
{
	char	*p;

	p = NULL;
	while (*env != NULL)
	{
		p = ft_strnstr(*env, "PATH=", 5);
		if (p != NULL)
			return (p + 5);
		env++;
	}
	return (NULL);
}
