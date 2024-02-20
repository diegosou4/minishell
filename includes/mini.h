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


typedef struct pipe
{
	char *path;
	char		**args;
	int 	here_doc;
	int		fd[2];
	int 	append;
	struct pipe *next;
	
}				t_pipe;

typedef struct words
{
	char *value;
	int flag;
} t_words;

typedef struct words_containt
{
	t_words *next;

};
