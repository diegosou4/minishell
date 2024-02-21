/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:42:35 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 09:44:44 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	*ft_parse_manager(char **env)
{
	char	*line;
	char **cpyenv;

	cpyenv = ft_arrcpy(env);
	//char 	*pwd;
	//pwd = ft_getpwd(env,"PWD=/");
	//printf("/%s \n", pwd);
	while (1)
	{
		line = readline("🐧>shell:$");
		if (!line)
			break ;
		add_history(line);
		ft_create_string(line,cpyenv);
		free(line);
	}
	return (NULL);
}
