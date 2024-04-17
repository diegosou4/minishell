/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 16:54:59 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	erro_cd(char *str, char *erro)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(erro, 2);
	ft_putstr_fd("\n", 2);
	free(str);
	return (get_file_num()->exit_code = EXIT_FAILURE);
}

int	case_cd(char *diretory, t_env **env)
{
	if (ft_strncmp("..", diretory, 2) == 0)
		invert_pwd(env);
	else
		change_old(env);
	free(diretory);
	return (EXIT_SUCCESS);
}

void	have_key(char *str, t_env **cpyenv, int token)
{
	int	key;

	key = key_exist(cpyenv, str, token);
	if (key == 1)
	{
		addbackenv(str, cpyenv, token);
		swap_value(cpyenv);
	}
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
		return (get_file_num()->exit_code = case_cd(str, env));
	erro = strerror(errno);
	erro_cd(str, erro);
	return (EXIT_FAILURE);
}
