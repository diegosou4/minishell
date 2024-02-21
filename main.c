/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:59:54 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 09:05:41 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mini.h"

/*
    1. check the access fucntion to get the path
    of te process.
    2. we can add the signal hanlder, in this part.
    */

int	main(int argc, char *argv[], char **env)
{  
	if (argc == 1 && argv[0])
		ft_parse_manager(env);
}
