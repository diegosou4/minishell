/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:25:54 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 12:25:56 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	flag_compare(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (str == NULL)
		return (0);

	if (str[i] == '-' && ft_strlen(str) > 1)
		flag = 1;
	i++;
	if(ft_strlen(str) > 1)
	{
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			flag = 0;
		i++;
	}
	}
	return (flag);
}

static void	first_flag(t_cmd *cmd)
{
	int	flag;
	int	spaces;
	int	i;

	flag = 0;
	spaces = 0;
	i = 2;
	while (cmd->args[i] != NULL)
	{
		flag = flag_compare(cmd->args[i]);
		if (flag == 1)
			i++;
		else
		{
			if (spaces > 0)
				printf(" ");
			printf("%s", cmd->args[i]);
			spaces++;
			i++;
		}
	}
}

static void	second_flag(t_cmd *cmd)
{
	int	spaces;
	int	i;

	spaces = 0;
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (spaces > 0)
			printf(" ");
		printf("%s", cmd->args[i]);
		spaces++;
		i++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	firstflag;

	firstflag = flag_compare(cmd->args[1]);
	if (firstflag == 1)
		first_flag(cmd);
	else
	{
		second_flag(cmd);
		printf("\n");
	}
	return (g_exit_status = EXIT_SUCCESS);
}
