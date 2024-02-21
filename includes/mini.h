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

#ifndef MINI_H
# define MINI_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // Signal handler.
#include "src/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>



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
// Parsign handler. 

void *ft_parse_manager(char **env);


// Parsing utils. 
char *ft_strtok(char *str, const char *delimiters);
// this will make a treatment to the sting. 
int ft_special_case(char *modified_line, int j, char **line);
int ft_parse_handler(char *str, const char *delimiters);
char *ft_create_string(char *line);

void ft_echo(int fd ,char *str, int flag);
int ft_whitespace(char *line);
// Get Path
char	*ft_getenv(char **env, char *str);
char    *ft_getpwd(char **env,char *str);
#endif



