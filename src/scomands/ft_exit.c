/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/07 22:01:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_numberforexit(char *str)
{
	int				i;
	unsigned char	res;

	i = ft_atoi(str);
	if (ft_strlen(str) > 1)
	{
		if (!(str[1] >= '0' && str[1] <= '9'))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			free(str);
			exit(2);
		}
	}
	free(str);
	res = (unsigned char)i;
	exit(res);
}


static void ft_freepids(void)
{
	if (get_file_num()->bash->pid != NULL)
	{
		free(get_file_num()->bash->pid);
		get_file_num()->bash->pid = NULL;
	}
}



static void ft_exitaux(t_cmd *comands,t_bash *bash_boss, char *str)
{
	int i;
	int len;
	
	i = 0;
	len = len_darray(comands->args);
	if (len == 2)
	{
		str = ft_strdup(comands->args[1]);
		ft_free_cmd_structure(bash_boss->commands);
		while (str[i] != '\0')
		{
			if (ft_isdigit(str[i]) != 1)
			{
				free(str);
				exit_msg("exit: numeric argument required\n");
			}
				
			i++;
		}
		ft_numberforexit(str);
	}
	else
	{
		if(len > 2)
			exit_msg("exit: too many arguments");
		ft_free_cmd_structure(bash_boss->commands);
		ft_freepids();
		exit(EXIT_SUCCESS);
	}
		
}
void	ft_exit(t_cmd *comands)
{
	char	*str;
	int		int_len;
	t_bash	*bash_boss;
	
	str = NULL;
	int_len = 0;
	if(ft_strncmp(comands->args[0],"exit",4) == 0)
		ft_putstr_fd(ANSI_COLOR_GREEN "exit, see you 😉\n" ANSI_COLOR_RESET, 2);
	ft_freepids();
	bash_boss = (get_file_num()->bash);
	ft_free_exit_status(bash_boss->line, bash_boss->cpyenv, bash_boss->env);
	ft_exitaux(comands,bash_boss,str);
}
