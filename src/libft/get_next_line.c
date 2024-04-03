/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:47:08 by diegmore          #+#    #+#             */
/*   Updated: 2023/11/14 16:47:10 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr_gnl(char *str, int start, int len_str)
{
	int		i;
	char	*subs;
	int		sum;

	i = 0;
	sum = len_str - start;
	if (sum == 0 || !str)
	{
		free(str);
		return (NULL);
	}
	subs = (char *)malloc(sizeof(char) * (sum + 1));
	if (!subs)
		return (NULL);
	while (str[start])
	{
		subs[i] = str[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	free(str);
	return (subs);
}

static void	ft_free_gnl(char **str, char *buffer)
{
	free(buffer);
	free((*str));
	(*str) = NULL;
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes_read != 0 && !(ft_strchr_gnl(str, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_free_gnl(&str, buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	free(buffer);
	buffer = ft_rnewline(str);
	str = ft_substr_gnl(str, ft_strlen_gnl(buffer), ft_strlen_gnl(str));
	return (buffer);
}
