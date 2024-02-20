/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:40:37 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/20 12:40:39 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "src/libft/libft.h"


typedef struct  s_redir
{
	char *str;
	int		fd;
	struct  s_redir *next;
}				t_redir;


typedef struct  s_cmd
{
	char *path;
	char		**args;
	int		fd[2];
	t_redir *redir;
	struct  s_cmd *next;
	
}				t_cmd;


