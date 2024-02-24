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

/*
    This function manages the parsing process of the input line before tokenization.
    It handles some cases that are easier to identify at the beginning of the parsing process.

    Arguments:
        - env: Pointer to the environment variables array.

    Idea:
    The function continuously reads input lines from the user until the user exits the shell.
    For each input line, it checks for certain conditions before tokenization, such as double pipes,
    redirections, and void inputs, to handle them appropriately.
    After checking the input line, it frees the memory allocated for the input line.
*/

void	*ft_parse_manager(char **env)
{
	char	*line;
	char **cpyenv;
	t_operations operations;

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
		if (ft_check_input(line, &operations))
			ft_create_string(line,cpyenv);
		free(line);
	}
	return (NULL);
}
