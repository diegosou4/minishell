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
#include <sys/wait.h>
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
	char *path;
	int 	token;
	int 	fd;
	struct s_redir *next;
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

void cmdinback(t_cmd **comands,char *args);
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
void initredir(t_redir **redir, int flag, char *file);
char *ft_strrange(char *s, int start, int end);
char *cleantoken(char *str, int c);
char *findfile(char *cmd);


// Functions for Exec
int casetoken(t_redir *redir);
int openredir(t_redir *redir);
void execute_cmd(t_cmd *commands, char **env);
void execution(t_cmd *commands, char **env);
void exec(t_cmd *command,int in, int out,char **env);

// Free and close
void closeandfree(t_redir *redir);
int closeredir(t_redir *redir);
int len_darray(char **arr);

// Case Redirects
int case_in(t_redir *redir);
int case_out(t_redir *redir);

// Pipes 
int sizepipe(t_cmd *commands);
int sizeredir(t_redir *redir);
void free_commands(t_cmd *comands);
void free_redirects(t_redir *redir);
// Builtings

int check_builtings(t_cmd *commands, char **env);
int 	index_env(char **env, char *str);
char	*ft_getenv(char **env, char *str, int i);
char    *ft_getpwd(char **env,char *str);
int ft_cd(char **env,t_cmd *comands);
void execute_pwd(char **env, t_cmd *commands);
void ft_env(char **env);
void execute_env(char **env, t_cmd *commands);
//int check_builtings(t_cmd *commands, char **env);
void execute_simple(t_cmd *commands, char **env);
void print_pwd(char **env,char *str);
char   *ft_getpwd(char **env,char *str);
void ft_export(char **env,t_cmd *commands);
int have_inenv(char **env, char *str);

#endif


