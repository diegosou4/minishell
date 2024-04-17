/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:41:46 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 11:24:35 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	exit_error(t_bash *bash_boss, char **new, int status)
{
	ft_free_double_pointers(new);
	free_here(bash_boss);
	free_pids(bash_boss);
	exit(status);
}

void	ft_notpermission(t_bash *bash_boss, char **new)
{
	ft_putstr_fd(" Permission denied\n", 2);
	exit_error(bash_boss, new, 126);
}
