/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/02 18:12:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	erro_cd(char *str, char *erro)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(erro, 2);
	ft_putstr_fd("\n", 2);
}
int	case_cd(char *diretory, t_env **env)
{
	char	*str;

	str = NULL;
	if (ft_strncmp("..", diretory, 2) == 0)
		invert_pwd(env);
	else
		change_old(env);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *comands, t_env **env)
{
	int		result;
	char	*erro;
	int		len;
	char	*str;

	str = NULL;
	len = len_darray(comands->args);
	if (len > 2)
		return (return_error("cd : too many arguments\n"));
	else if (len == 1 || ft_strncmp("~", comands->args[1], 1) == 0)
	{
		str = get_valuepwd(env, "HOME=");
		if (str == NULL)
			return (return_error("Home not set\n"));
	}
	else
		str = ft_strdup(comands->args[1]);
	result = chdir(str);
	if (result == 0)
	{
		case_cd(str, env);
		return (g_exit_status = EXIT_SUCCESS);
	}
	erro = strerror(errno);
	erro_cd(str, erro);
	return (g_exit_status = EXIT_FAILURE);
}
