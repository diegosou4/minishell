/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:51:49 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/03 18:58:55 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	return_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	g_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

int	error_unset(char *key)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not found\n", 2);
	free(key);
	g_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

void exit_msg(char *str)
{
	ft_putstr_fd(str,2);
	exit(EXIT_FAILURE);
}

void export_msg(char *arr)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arr, STDERR_FILENO);
	ft_putstr_fd(" : not a valid identifier", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}