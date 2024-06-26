/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:54:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/21 22:27:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_expand(t_cmd **commads, char **cpyenv)
{
	t_cmd	*ptr;
	char	*path;
	char	*blackslash;
	t_cmd	*newptr;

	ptr = (*commads);
	if (!ptr)
		return ;
	path = ft_getenv(cpyenv, "PATH=/", FALSE);
	while (ptr != NULL)
	{
		blackslash = ft_strjoin("/", ptr->args[0]);
		ptr->path = ask_acess(blackslash, path);
		free(blackslash);
		ptr = ptr->next;
	}
	newptr = (*commads);
	while (newptr != NULL)
	{
		printf("PATH: %s\n", newptr->path);
		newptr = newptr->next;
	}
}

static char	*ft_strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	return (dest);
}

static void	*free_malloc(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_arrcpy(char **str)
{
	int		i;
	int		j;
	int		len;
	char	**str_copy;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (ft_calloc(1, sizeof(char *)));
	while (str[i])
		i++;
	str_copy = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!str_copy)
		return (NULL);
	while (j < i)
	{
		len = strlen(str[j]);
		str_copy[j] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!str_copy[j])
			return (free_malloc(str_copy, j));
		ft_strcpy(str_copy[j], str[j]);
		j++;
	}
	return (str_copy);
}

char	**ft_arrplus(char **str, char *new)
{
	int		i;
	int		j;
	int		len;
	char	**str_copy;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i])
		i++;
	str_copy = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!str_copy)
		return (NULL);
	while (j < i)
	{
		len = strlen(str[j]);
		str_copy[j] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!str_copy[j])
			return (free_malloc(str_copy, j));
		ft_strcpy(str_copy[j], str[j]);
		j++;
	}
	ft_strcpy(str_copy[j], new);
	return (str_copy);
}
