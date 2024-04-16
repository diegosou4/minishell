/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:33:37 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 01:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ft_strrange(char *s, int start, int end)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = (end - start) + 1;
	str = (char *)ft_calloc(sizeof(char), len);
	while (i < (len - 1))
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*findfile(char *cmd)
{
	int		i;
	int		start;
	char	*file;
	char	*newfile;

	i = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] > 6 && cmd[i] != '\0')
			i++;
		start = i;
		if (cmd[i] <= 5)
			break ;
	}
	file = ft_strrange(cmd, 0, start);
	newfile = cleantoken(file, 50);
	free(file);
	return (newfile);
}

int	checkcase(char c)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (c == i)
			return (i);
		i++;
	}
	return (0);
}

void	addbackredir(t_redir *redir, char *file, int flag)
{
	t_redir	*ptr;
	t_redir	*last;

	last = redirnew();
	checkpathredir(last, file, flag);
	ptr = redir;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = last;
}

void	initredir(t_redir **redir, int flag, char *file)
{
	if (*redir == NULL)
	{
		*redir = redirnew();
		checkpathredir(*redir, file, flag);
	}
	else
		addbackredir(*redir, file, flag);
}
