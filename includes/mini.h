/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:40:39 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 01:20:44 by marvin           ###   ########.fr       */
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
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "src/libft/get_next_line.h"

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
#define ANSI_COLOR_PURPLE "\e[0;35m"

typedef enum s_bool
{
	TRUE,
	FALSE,
} t_bool;

//________________________________STRUCTURES__FOR THE TOKENS_________________________________

// Words with the flags...

typedef enum s_tags
{
	WORD, 
	EXCECUTOR,
	VARIABLE,
	SPECIAL_PAR,
	SPECIAL_VAR,
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
	struct s_word_list *next; // Pointer to the next node in the list
	t_word_desc *word;		  // Pointer to the word descriptor
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
	int token;
	struct s_env *next;
} t_env;


typedef struct  s_redir
{
	char *path;
	int 	token;
	int 	fd;
	struct s_redir *next;
}				t_redir;

//________________________________STRUCTURES__FOR THE COMMANDS_________________________________

typedef struct s_cmd
{
	char *path;
	char **args;
	int pipesfd[2];
	int fd_final[2];
	int executable;
	t_redir *redir;
	struct s_cmd *next;

} t_cmd;
// Parsign handler.

void *ft_parse_manager(char **env);

// Parsing utils.
char *ft_strtok(char *str, const char *delimiters);
// this will make a treatment to the sting.
int ft_special_case(char *modified_line, int j, char **line);
int ft_parse_handler(char *str, const char *delimiters);


int ft_whitespace(char *line);

void cmdinback(t_cmd **comands,char *args);
// Get Path
char *ft_getenv(char **env, char *str, t_bool i);

void cmdinback(t_cmd **comands, char *args);
void ft_expand(t_cmd **commads, char **cpyenv);
char **ft_arrcpy(char **str);
char *ask_acess(char *comand, char *path);

// Struct redir
t_cmd *cmdnew(char *args);
t_cmd *putcmds(char *args);
t_redir *redirnew(void);
// t_redir *addredirnew(int flag);
// void add_redir(t_cmd **commands);
//  Checker quotes.
void ft_checker_quotes(char *str);
char *findpath(char **args, int flag, int location);
char *ft_parse_redir(char *str);

// ________________________________________________________Print Utilities ________________________________
void ft_print_doble_char(char **argv);
void ft_print_list_struct(t_word_list *structure);

// check input.
int ft_check_input(char *line);
int ft_check_redir_pipes(char **line);

// Fuctions for redir

t_redir *haveredir(char *cmd);
void checkpathredir(t_redir *redir, char *file, int flag);


void initredir(t_redir **redir, int flag, char *file);
char *ft_strrange(char *s, int start, int end);
char *cleantoken(char *str, int c);
char *findfile(char *cmd);


// Free and close
void closeandfree(t_redir *redir);
int closeredir(t_redir *redir);

// Pipes 
int sizepipe(t_cmd *commands);
int sizeredir(t_redir *redir);
void free_commands(t_cmd *comands);
void free_redirects(t_redir *redir);
// Builtings


int check_builtings(t_cmd *commands);
t_env *newexp(char *str, int this, int token);

void ft_numberforexit(char *str);


// ENV STRUCT
char *get_key(char *str);
t_env *newsenv(char *str, int this, int token);
t_env *ft_nenv(char **env,int token);
void addbackenv(char *str,int this,t_env **cpyenv, int token);


// HERE DOC
int redirout(char *path);
int ft_append(char *path);
int ft_heredoc(char *delimiter);
void ft_putforwe(char *line,int fd);

// __________________________________________________Fuctions_Test_____________________________
int ft_handle_redir_input(char *delimiter);
// Check redir.
int ft_check_valid_redir(t_word_list *word_list);

// Signal Handler.

void ft_signal_manager();
void handle_signal(int signal1);

// __________________________________________________FREE_MANAGER ________________________________

void ft_free_double_pointers(char **split_line);
void close_pipes(t_cmd **cmd);

// __________________________________________________LIST_MANAGER ________________________________
int ft_extract_var(t_word_list *word_list, char **env);
t_word_list	*ft_lstlast_(t_word_list *lst);
int ft_check_struct_redir(t_word_list *tokens);

//___________________________________________________QUOTES REMOVAL _______________________________
void ft_quotes_remove(t_word_list *word_list);


//___________________________________________________Test Execution____________________________________


void check_path(t_cmd **commands, char **env);
int check_path2(t_cmd **commands, char **env);

//_____________________________________________________ENV ______________________________________________________
void ft_env_null();

//_________________________________________________ EXEC

int ft_countpipes(t_cmd *cmd);
void open_pipes(t_cmd **cmd);

void start_exection(t_cmd **commands,char **env,t_env **cpy);
void ft_magane_executor(t_cmd **cmd, char **env,t_env **cpy);
void child_executor(t_cmd *curr,char **env,t_env **cpy,t_cmd *last);
void ft_close(t_cmd **commands);

int redir_error(int fd);
int ft_howpipes(t_cmd *comands);	
void child_builtings(t_cmd **cmd, t_env **cpy);
//______________________________________________FILES___________________________________________________//

int open_redir(t_cmd **commands);
int open_fd(t_redir **redirect);


//_________________________________________________FT_ECHO_____________________________________________//
int ft_echo(t_env *cmd);

//_________________________________________________ERROR______________________________________________//
int return_error(char *str);
//_______________________________________________FT_CD_______________________________________________//
int ft_cd(t_cmd *comands,t_env **env);
//________________________________________________FT_ENV_____________________________________________//
int ft_env(t_env *env);
int execute_env(t_env *env, t_cmd *commands);
//________________________________________________FT_EXP_____________________________________________//

int ft_exp(t_env *env);
int ft_export(t_env **env,t_cmd *commands);
int ft_haveinenv(t_env *env, char *str);
int ft_indexinenv(t_env *env,char *this);
int index_env(char **env, char *str);
int ft_casewithout(t_env **env,char *command);
int ft_caseequal(t_env **env,char *command);
void ft_putinlast(t_env **env,char *this,int token);
//________________________________________________FT_PWD________________________________________________//
int print_pwd(void);
//_______________________________________________FT_UNSET____________________________________________//
int ft_unset(t_env **env,t_cmd *commands);
void ft_removeinenv(t_env **env, int index);
void update_index(t_env **env);
//________________________________________________EXIT_______________________________________________//
void ft_exit(t_cmd *comands);

//____________________________________________EXECUTEBUILTINGS_______________________________________//
int execute_builtings(t_cmd **cmd,t_env **cpy, int check);

//___________________________________________________VAR EXP _______________________________
char *ft_path_handler(t_env *env, char *variable);

//--Create the array of structures.
t_word_list	*tokenize_and_print(char *token);
// __________________________________________________FREE_MANAGER ________________________________

void ft_free_double_pointers(char **split_line);
void ft_free_env_list(t_env *env);
void ft_free_line_struct(t_line *line);
void ft_free_double_word_list(t_word_list **word_desc);
void ft_free_t_word_list(t_word_list *word_list);
void ft_free_cmd_structure(t_cmd *cmd_structure);
void ft_free_redir_list(t_redir *redir);
void ft_free_tokens_new_string(char **tokens, char *new_string);
void ft_free_line_env(t_line *line, t_env *cpyenv);
void ft_print_list_struct(t_word_list *structure, int i);
void ft_print_cmd_struct(t_cmd *cmd);
t_word_lists	*ft_init_word_list(t_word_lists *word_lists, char *token);
void ft_flags_tags_assignment(t_word_list *word_list);
t_line *ft_init_manager(t_line *line);
char *ft_create_string(char *line);
void update_index(t_env **env);
void ft_putinlast(t_env **env,char *this);
void ft_export(t_env **env,t_cmd *commands);

#endif