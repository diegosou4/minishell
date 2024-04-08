/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:01:12 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/04 22:30:46 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	error_path(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
}

int	expand_path(t_cmd **commands, char **env)
{
	int		build;
	t_cmd	*ptr;
	char	*home;

	if (env == NULL)
		return (EXIT_FAILURE);
	home = ft_getpath(env);
	ptr = (*commands);
	build = check_builtings(ptr);
	if (build == 0 && ptr->args[0] == NULL)
		return (EXIT_SUCCESS);
	if (build != 0)
		ptr->path = ft_strdup(ptr->args[0]);
	else
		ptr->path = ask_acess(ptr->args[0], home);
	if (ptr->path == NULL)
	{
		error_path(ptr->args[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*givepath(t_env *env)
{
	char	*path;
	t_env	*ptr;
	int		index;

	path = NULL;
	ptr = env;
	index = ft_indexinenv(ptr, "PATH");
	if (env == NULL && index != -1)
		ft_putstr_fd("Error : Env not set\n", 2);
	else if(index == -1)
		ft_putstr_fd("Error : Path not set\n", 2);
	else if(index != -1)
	{
		while (index-- != 0)
			ptr = ptr->next;
		path = ft_strdup(ptr->value);
	}
	return (path);
}

int	expand_path_cpy(t_cmd **commands, t_env *cpyenv)
{
	int		build;
	t_cmd	*ptr;
	char	*home;

	ptr = (*commands);
	build = check_builtings(ptr);
	if (build == 0 && ptr->args[0] == NULL)
		return (EXIT_SUCCESS);
	if((access(ptr->args[0], F_OK) != 0 ) || build == 0)
	{
		home = givepath(cpyenv);
		if (home == NULL)
			return (EXIT_FAILURE);
		ptr->path = ask_acess(ptr->args[0], home);
		if(home != NULL)
			free(home);
		if (ptr->path == NULL)
		{
			error_path(ptr->args[0]);
			g_exit_status = 127;
			return (EXIT_FAILURE);
		}
	}else
	{
		ptr->path = ft_strdup(ptr->args[0]);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
