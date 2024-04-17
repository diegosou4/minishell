/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:33:33 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/17 16:56:40 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	print_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, FILENAME_MAX);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (get_file_num()->exit_code = EXIT_SUCCESS);
}
