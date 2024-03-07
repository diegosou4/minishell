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
#define MINI_H

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

/*
	Color codes.
*/

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef enum s_bool
{
	TRUE,
	FALSE,
} t_bool;

//________________________________STRUCTURES__FOR THE INPUT_________________________________

typedef struct s_line
{
	char *line;
	char *usr;
	char *line_text;
	char *color_line;
	char *value_env;
} t_line;

t_line *ft_init_manager(t_line *line);

//________________________________STRUCTURES__FOR THE TOKENS_________________________________

// Words with the flags...

typedef enum s_tags
{
	WORD, 
	EXCECUTOR,
	VARIABLE,
	SPECIAL_PAR,
	SPECIAL_VAR,
	VARIABLE_CHECK,
} t_tags;

typedef struct s_word_desc
{
	char *word;
	int flags;
	t_tags tags;
} t_word_desc;

// List of words with the flags...

typedef struct s_word_list
{
	struct s_word_list *next;
	t_word_desc *word;
	t_bool redirection;
} t_word_list;

//________________________________STRUCTURES__FOR THE REDIRECTIONS_________________________________

typedef enum s_rediopr
{
	redir_out = 1,
	redir_in = 2,
	here_doc = 3,
	append_out = 4,
	inandout = 5
} t_rediopr;


typedef struct s_env{

	int index;
	char *key;
	char *value;
	struct s_env *next;
} t_env;


typedef struct  s_redir
{
	char	*path;
	int 	token;
	int 	fd;
	struct s_redir *next;
}				t_redir;

//________________________________STRUCTURES__FOR THE COMMANDS_________________________________

typedef struct s_cmd
{
	char			*path;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;

} t_cmd;
// Parsign handler.

void *ft_parse_manager(char **env);
//________________________________PARSING UTILITIES_________________________________

char *ft_strtok(char *str, const char *delimiters);
void ft_line_handler(t_line *line, t_env *cpyenv);

// this will make a treatment to the sting.
int ft_special_case(char *modified_line, int j, char **line);
int ft_parse_handler(char *str, const char *delimiters);
char *ft_create_string(char *line);

void ft_echo(int fd, char *str, int flag);
int ft_whitespace(char *line);

void cmdinback(t_cmd **comands,char *args);
// Get Path
// char *ft_getenv(char **env, char *str, t_bool i);
char *ft_getpwd(char **env, char *str);

void cmdinback(t_cmd **comands, char *args);
// char *ft_cd(char *newlocal, char *old);
void ft_expand(t_cmd **commads, char **cpyenv);
char **ft_arrcpy(char **str);
t_cmd *returnmystruct(char *newline);
char *ask_acess(char *comand, char *path);

//________________________________STRUCT COMMANDS CREATION__________________________________

t_cmd *cmdnew(char *args);
t_cmd *putcmds(char *args);
t_redir *redirnew(void);
void ft_structure_creation(char *line, t_env *env);

//________________________________TOKEN MANAGER STRUCTURE CREATION___________________________
t_word_list **ft_tokenizer_manager(char *line, t_env *env);
// t_redir *addredirnew(int flag);
// void add_redir(t_cmd **commands);
//  Checker quotes.
void ft_checker_quotes(char *str);
char *findpath(char **args, int flag, int location);
char *ft_parse_redir(char *str);

// ________________________________________________________Print Utilities ________________________________
void ft_print_doble_char(char **argv);
void ft_print_list_struct(t_word_list *structure, int i);

// check input.
int ft_check_input(char *line);
int ft_check_redir_pipes(char **line);

// Fuctions for redir

t_redir *haveredir(char *cmd);
void checkpathredir(t_redir *redir, char *file, int flag);
void checkinoutredir(t_redir *redir, char *file, int flag);

void initredir(t_redir **redir, int flag, char *file);
char *ft_strrange(char *s, int start, int end);
char *cleantoken(char *str, int c);
char *findfile(char *cmd);


// Functions for Exec
int casetoken(t_redir *redir);
int openredir(t_redir *redir);

void execution(t_cmd *commands, t_env **env);

// Free and close
void closeandfree(t_redir *redir);
int closeredir(t_redir *redir);


// Case Redirects
int case_in(t_redir *redir);
int case_out(t_redir *redir);

// Pipes 
int sizepipe(t_cmd *commands);
int sizeredir(t_redir *redir);
void free_commands(t_cmd *comands);
void free_redirects(t_redir *redir);
// Builtings
int check_builtings(t_cmd *commands);

void update_index(t_env **env);
void ft_putinlast(t_env **env,char *this);
void ft_export(t_env **env,t_cmd *commands);

int 	index_env(char **env, char *str);


char	*ft_getenv(char **env, char *str, int i);
int ft_cd(t_cmd *comands,t_env **env);
void execute_env(t_env *env, t_cmd *commands);
int ft_haveinenv(t_env *env, char *str);
int ft_indexinenv(t_env *env,char *this);
void print_pwd(void);
void ft_removeinenv(t_env **env, int index);
void ft_unset(t_env **env,t_cmd *commands);


// ENV STRUCT
char *get_key(char *str);
t_env *newsenv(char *str, int this);
t_env *ft_nenv(char **env);
void addbackenv(char *str,int this,t_env **env);
void print_env(t_env *env);
void ft_env(t_env *env);

//void exec(t_cmd *command,int in, int out,char **env);
//void execute_cmd(t_cmd *commands, char **env);
//void ft_export(char ***env,t_cmd *commands);
//int have_inenv(char **env, char *str);
//int check_builtings(t_cmd *commands, char **env);


// Check redir.
int ft_check_valid_redir(t_word_list *word_list);

// Signal Handler.

void ft_signal_manager();
void handle_signal(int signal1);

// __________________________________________________FREE_MANAGER ________________________________

void ft_free_double_pointers(char **split_line);
void ft_free_env_list(t_env *env);
void ft_free_line_struct(t_line *line);

// __________________________________________________LIST_MANAGER ________________________________
int ft_extract_var(t_word_list *word_list, t_env *env);
t_word_list	*ft_lstlast_(t_word_list *lst);
int ft_check_struct_redir(t_word_list *tokens);

//___________________________________________________QUOTES REMOVAL _______________________________
void ft_quotes_remove(t_word_list *word_list);

//___________________________________________________VAR EXP _______________________________
char *ft_path_handler(t_env *env, char *variable);

#endif
