/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erros.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:25:50 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/20 15:25:53 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	printf_error_fd(char *strerror, char *file)
{
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}


void check_dir(t_bash *bash_boss,t_cmd *cmd, char **new)
{
	int checkdir;
	checkdir = - 1;
	checkdir = chdir(cmd->path);
	if(checkdir == 0)
	{
		ft_putstr_fd("Is a directory\n",2);
		ft_free_double_pointers(new);
		free_pids(bash_boss);
		free_here(bash_boss);
		exit(126);
	}
}
