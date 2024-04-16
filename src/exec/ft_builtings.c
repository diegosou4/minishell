/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:08:24 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/27 11:08:25 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	check_builtings(t_cmd *commands)
{
	int	len;

	len = ft_strlen(commands->args[0]);
	if (commands->args[0] == NULL)
		return (0);
	else if (ft_strncmp("pwd", commands->args[0], len) == 0)
		return (1);
	else if (ft_strncmp("cd", commands->args[0], len) == 0)
		return (2);
	else if (ft_strncmp("env", commands->args[0], len) == 0)
		return (3);
	else if (ft_strncmp("export", commands->args[0], len) == 0)
		return (4);
	else if (ft_strncmp("unset", commands->args[0], len) == 0)
		return (5);
	else if (ft_strncmp("echo", commands->args[0], len) == 0)
		return (6);
	else if (ft_strncmp("exit", commands->args[0], len) == 0)
		return (7);
	return (0);
}

int	execute_builtings(t_cmd **cmd, t_env **cpy, int check)
{
	if (check == 1)
		return (print_pwd((*cmd)));
	else if (check == 2)
		return (ft_cd((*cmd), cpy));
	else if (check == 3)
		return (execute_env((*cpy), (*cmd)));
	else if (check == 4)
		return (ft_export(cpy, (*cmd)));
	else if (check == 5)
		return (ft_unset(cpy, (*cmd)));
	else if (check == 6)
		return (ft_echo((*cmd)));
	else if (check == 7)
	{
		ft_exit((*cmd));
		return (0);
	}
	return (0);
}
