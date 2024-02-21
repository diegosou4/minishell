/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:26:07 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 23:34:50 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*ask_acess(char *comand, char *path)
{
	char	**paths;
	int		i;
	char	*cplusp;

	paths = mysplit(path, ':', 0);
	i = 0;
	while (paths[i])
	{
		cplusp = ft_strjoin(paths[i], comand);
		if (access(cplusp, F_OK) == 0)
		{
			free(cplusp);
			cplusp = ft_strdup(paths[i]);
			free_paths(paths);
			return (cplusp);
		}
		free(cplusp);
		i++;
	}
	free_paths(paths);
	return (NULL);
} 

char	*ask_command(char *comand)
{
	char	*str;

	if (access(comand, F_OK) == 0)
	{
		str = ft_strdup(comand);
		return (str);
	}
	return (NULL);
}

char	*checkpath(char **path, char *command)
{
	int		i;
	char	*path_value;
	char	*comandf;

	i = 0;
	path_value = NULL;
	while (path[i] != NULL)
	{
		comandf = ft_strjoin("/", command);
		path_value = ft_strjoin(path[i], comandf);
		if (access(path_value, F_OK) == 0)
		{
			free(path_value);
			free(comandf);
			return (ft_strdup(path[i]));
		}
		free(path_value);
		free(comandf);
		i++;
	}
	return (NULL);
}



