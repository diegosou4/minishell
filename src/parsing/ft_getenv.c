/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:14 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/21 19:54:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	index_env(char **env, char *str)
{
	char	*p;
	int		i;
	int		j;

	p = NULL;
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		p = ft_strnstr(env[i], str, ft_strlen(str));
		if (p != NULL)
			return (i);
		i++;
	}
	return (-1);
}

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
