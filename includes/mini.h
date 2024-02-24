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
#include <fcntl.h>
#include <unistd.h>

typedef enum s_bool{
	TRUE,
	FALSE,
} t_bool;


typedef enum s_rediopr {
	redir_out = 1,
	redir_in = 2,
	here_doc = 3,
	append_out = 4,
	inandout = 5
} t_rediopr;


typedef struct s_operations
{
	char *pipe;
	char *redir_input;
	char *redir_output;
	char *here_doc;
	char *apppend_out;
} t_operations;

typedef struct  s_redir
{
	char *pathout;
	char *pathin;
	int 	token;
	int 	in;
	int		out;
}				t_redir;

typedef struct  s_cmd
{
	char *path;
	t_bool	literal;
	t_bool	fint_variable;
	char		**args;
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
char *ft_create_string(char *line, char **env);

void ft_echo(int fd ,char *str, int flag);
int ft_whitespace(char *line);
// Get Path
char	*ft_getenv(char **env, char *str);
char    *ft_getpwd(char **env,char *str);

void cmdinback(t_cmd **comands,char *args);
char *ft_cd(char *newlocal, char *old);
void ft_expand(t_cmd **commads, char **cpyenv);
char **ft_arrcpy(char **str);
t_cmd   *returnmystruct(char *newline);
char	*ask_acess(char *comand, char *path);

// Struct redir
t_cmd *cmdnew(char *args);
t_cmd *putcmds(char *args);
t_redir *redirnew(void);
//t_redir *addredirnew(int flag);
//void add_redir(t_cmd **commands);
// Checker quotes. 
void ft_checker_quotes(char *str, t_cmd *structure);
char *findpath(char **args, int flag, int location);
char *ft_parse_redir(char *str);

// Print a double list
void ft_print_doble_char(char **argv);

// Init the operation structure.
void ft_init_operations(t_operations *operations);

// check input.
int ft_check_input(char *line, t_operations *operations);


// Fuctions for redir

t_redir *haveredir(char *cmd);
void checkpathredir(t_redir *redir, char *file, int flag);
void checkinoutredir(t_redir *redir, char *file, int flag);
void initredir(t_redir *redir, int flag,char *file);
char *ft_strrange(char *s, int start, int end);
char *cleantoken(char *str, int c);
char *findfile(char *cmd);
#endif


