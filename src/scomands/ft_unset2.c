/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:11:45 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/16 16:23:47 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	parse_env(t_env **env, char *str)
{
	char	c;

	c = '=';
	if (ft_boolstrchr(str, c) == 1)
	{
		return (unset_env(env, str, (int)0, 0));
	}
	else
		return (unset_env(env, str, (int)-1, 0));
}

int	ft_unset(t_env **env, t_cmd *commands)
{
	int	exit;
	int	i;

	exit = 0;
	i = 1;
	if (*env == NULL)
		return (return_error("Error : env not set\n"));
	if (len_darray(commands->args) == 1)
		return (	get_file_num()->exit_code = EXIT_SUCCESS);
	while (commands->args[i] != NULL)
	{
		if (ft_strncmp("_=", commands->args[i], 2) == 0)
			exit = (EXIT_SUCCESS);
		else
			exit = parse_env(env, commands->args[i]);
		i++;
	}
	return (	get_file_num()->exit_code = exit);
}
