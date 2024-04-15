
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:40:39 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/21 18:59:50 by marvin           ###   ########.fr       */
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
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "src/libft/get_next_line.h"
# include <sys/ioctl.h> /* */

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
#define A_C_P "\e[0;35m"

#define MAIN 1
#define HERE 2
//_______________________Exit status _________________
extern int g_exit_status;

typedef struct s_bash t_bash;
typedef struct s_word_list t_word_list;
typedef struct s_line t_line;

typedef struct {
	int in;
	int out;
	int exit_code;
	int heredoc;
	t_line *line;
	t_bash *bash;
	t_word_list **list;
	char **env;
} t_file_struct;

typedef struct s_number
{
	int j;
	int i;
	char flag_quotes;
} t_number;

typedef enum s_bool
{
	TRUE,
	FALSE,
} t_bool;

//________________________________STRUCTURES__FOR__THE INPUT_________________________________

typedef struct s_line
{
	char *line;
	char *usr;
	char *line_text;
	char *color_line;
	char *value_env;
} t_line;

//________________________________STRUCTURES__FOR THE TOKENS_________________________________

// Words with the flags...

typedef enum s_tags
{
	WORD,
	EXCECUTOR,
	VARIABLE,
	SPECIAL_VAR,
	VARIABLE_CHECK,
	PATH,
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
	t_word_desc *word;
	t_bool redirection;
	struct s_word_list *next;
} t_word_list;

typedef struct s_word_lists
{
	char		*subtoken;
	t_word_desc	*word_desc;
	t_word_list	*node;
	t_word_list	*head;
	t_word_list	*current_token;

} t_word_lists;
//________________________________STRUCTURES__FOR THE REDIRECTIONS_________________________________

typedef enum s_rediopr
{
	redir_out = 1,
	redir_in = 2,
	here_doc = 3,
	append_out = 4,
	inandout = 5,
	open_here = 6
} t_rediopr;


typedef struct s_env{

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
	int executable;
	int pipes[2];
	t_redir *redir;
	struct s_cmd *next;
	struct s_cmd *prev;

} t_cmd;
// Parsign handler.

typedef struct s_bash
{
	t_cmd *commands;
	int *pid;
	int in;
	int out;
	int fdin;
	int fdout;
	int pipein;
	int pipeout;
	int exit_status;
	char **env;
	t_env *cpyenv;
	t_line *line;
	t_word_list **list;
	
} t_bash;

void *ft_parse_manager(char **env);

// Parsing utils.
char *ft_strtok(char *str, const char *delimiters);
// this will make a treatment to the sting.
int ft_special_case(char *modified_line, int j, char **line);
int ft_parse_handler(char *str, const char *delimiters);


int ft_whitespace(char *line);

void cmdinback(t_cmd **comands,char *args);
// Get Path
char *ft_getenv(char **env, char *str, int i);

void cmdinback(t_cmd **comands, char *args);
void ft_expand(t_cmd **commads, char **cpyenv);
char **ft_arrcpy(char **str);
char	*ask_acess(char *comand, char *path);

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

// check input.
int ft_check_input(char *line, t_bash *bash);
int ft_check_redir_pipes(char **line);

// Fuctions for redir

t_redir *haveredir(char *cmd);
void checkpathredir(t_redir *redir, char *file, int flag);


void initredir(t_redir **redir, int flag, char *file);
char *ft_strrange(char *s, int start, int end);
char *cleantoken(char *str, int c);
char *findfile(char *cmd);


// Free and close
void exit_msg(char *str);
void close_fderror(t_redir *redir);

// Pipes 
int sizepipe(t_cmd *commands);
void set_pipes(t_cmd *ptrcmd);
void care_myprev(t_cmd *ptrcmd);
void care_inchild(t_cmd *current, t_bash *bash_boss);
// Builtings


int check_builtings(t_cmd *commands);

void ft_numberforexit(char *str);


// ENV STRUCT
char *get_key(char *str);
t_env *newsenv(char *str, int token);
t_env *ft_nenv(char **env,int token);
void addbackenv(char *str,t_env **cpyenv, int token);
int len_env(t_env *env);



t_cmd *ft_structure_creation(t_word_list **token_list);
t_redir *ft_parse_redir_create(t_word_list *token_list);
t_cmd *ft_parse_array(t_word_list *words_list);
t_redir *ft_create_node(void); // node redir creation
void ft_init_redir_node(t_redir *node, char *path, int token);
void ft_line_handler(t_line *line, t_env *cpyenv, int num);

// __________________________________________________Fuctions_Test_____________________________
int ft_handle_redir_input(char *delimiter);
// Check redir.
int ft_check_valid_redir(t_word_list *word_list);

// Signal Handler.

void ft_signal_manager();
void handle_signal(int signal1);
void	handle_signal_here_doc(int signal1);
void	handle_signal_child(int signal1);
void	ft_signal_manager_child(void);
void	ft_signal_manager_here(void);
t_file_struct *get_file_num();
// __________________________________________________FREE_MANAGER ________________________________

void ft_free_double_pointers(char **split_line);

// __________________________________________________LIST_MANAGER ________________________________
void ft_extract_var(t_word_list *word_list, t_bash *bash);
t_word_list	*ft_lstlast_(t_word_list *lst);
int ft_check_struct_redir(t_word_list *tokens);

//___________________________________________________QUOTES REMOVAL _______________________________
void ft_quotes_remove(t_word_list *word_list);


//___________________________________________________Test Execution____________________________________


void check_path(t_cmd **commands, char **env);
int check_path2(t_cmd **commands, char **env);

//_____________________________________________________ENV ______________________________________________________
void ft_env_null();
//_____________________________________________________HERE_DOC___________________________________________________//
void check_heredoc(t_redir **redirect, t_cmd *cmd,t_bash *bash_boss);
void check_here(t_bash *bash_boss,t_cmd *cmd);
int	ft_heredoc(char *delimiter, t_bash *bash_boss, t_cmd *cmd);
int ft_putforwe(char *line,int fd);
void free_here(t_bash *bash_boss);

//_________________________________________________ EXEC
void care_redirect(t_cmd **cmd,t_bash **bash_boss);
void care_expand(t_cmd **cmd,t_bash **bash_boss);
void dup_final(t_bash *bash_boss,t_cmd *cmd);
void check_dir(t_bash *bash_boss,t_cmd *cmd,char **new);
int	return_in(t_bash *bash_boss,t_redir *ptr);
int	return_out(t_bash *bash_boss,t_redir *ptr);
void	error_path(char *str);
void close_error(t_bash *bash_boss);
void redir_inchild(t_bash *bash_boss);
void start_execution(t_bash *bash_boss);
void ft_magane_executor(t_bash *bash_boss);
void child_build(t_cmd *cmd, t_bash *bash_boss);
int simple_bexecutor(t_cmd *ptrcmd,t_bash *bash_boss,int check);
void pipes_executor(t_cmd *ptrcmd,t_bash *bash_boss);
void fail_expander(t_bash *bash_boss,t_cmd *cmd);
int ft_howpipes(t_cmd *comands);
void close_myhere(t_cmd *cmd);
void close_myhereprev(t_cmd *cmd);
void close_myherenext(t_cmd *cmd);
//_____________________________________________PIDS_____________________________________________________//
void alloc_mypids(t_bash *bash_boss);
void wait_mypids(t_bash *bash_boss);
void free_pids(t_bash *bash_boss);
//______________________________________________FILES___________________________________________________//

int open_redir(t_cmd **commands);
int open_out(char *path);
int open_in(char *path);
int open_append(char *path);
int open_fd(t_redir **redirect);
void close_pipes(t_cmd *commands);
void printf_error_fd(char *strerror,char *file);
void init_dup(t_bash *bash_boss);
void reset_fd(t_bash *bash_boss, int i);
void dup_fd(t_bash *bash_boss);
void close_dup(t_bash *bash_boss);
void close_fds(t_bash *bash_boss);
//_________________________________________________FT_ECHO_____________________________________________//
int ft_echo(t_cmd *cmd);

//_________________________________________________ERROR______________________________________________//
int return_error(char *str);
//_______________________________________________FT_CD_______________________________________________//
int ft_cd(t_cmd *comands,t_env **env);
void change_old(t_env **env);
void invert_pwd(t_env **env);

int case_cd(char *diretory,t_env **env);
char *get_valuepwd(t_env **env, char *value);
void change_pwd(t_env **env);
//________________________________________________FT_ENV_____________________________________________//
int ft_env(t_env *env);
int execute_env(t_env *env, t_cmd *commands);
void	change_value(char **key, char **value, char *str);
int	key_exist(t_env **env, char *str, int token);
void	swap_value(t_env **env);
//________________________________________________FT_EXP_____________________________________________//
int export_env(t_env **env,char *str);
void have_key(char *str,t_env **cpyenv,int token);
int ft_exp(t_env *env);
int ft_indexinenv(t_env *env,char *this);
int case_plus(t_env **env,char *str,int token);
void export_msg(char *arr);
//________________________________________________FT_PWD________________________________________________//
int print_pwd(t_cmd *comands);
//_______________________________________________FT_UNSET____________________________________________//
int ft_unset(t_env **env,t_cmd *commands);
int error_unset(char *key);
int unset_env(t_env **env,char *str);
//________________________________________________EXIT_______________________________________________//
void	ft_exit(t_cmd *comands);
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
void ft_free_exit_status(t_line *line, t_env *cpyenv, char **env);
void ft_free_list_tokens(t_word_list **word_list, char **tokens, char *new_string, t_bash *bash);
void	ft_free_wd_list_char(t_word_list **word_list, char *new_string);
void ft_print_list_struct(t_word_list *structure, int i);
void ft_print_cmd_struct(t_cmd *cmd);
t_word_list	*ft_init_word_list(t_word_list *word_lists, char *token);
void ft_flags_tags_assignment(t_word_list *word_list);

//_____________________________________________INIT_MANAGER____________________________________
t_line *ft_init_manager(t_line *line);
void ft_bash_boss_init(t_bash *bash, char **env);

char *ft_create_string(char *line, t_bash *bash);
void update_index(t_env **env);
int ft_export(t_env **env,t_cmd *commands);
//______________________________________________EXPAND_PATH_______________________________________________//
int expand_path(t_cmd **commands,char **env);
int expand_path_cpy(t_cmd **commands,t_env *cpyenv);
char *ft_getpath(char **env);

void execute_one(t_cmd *command,char **env,t_env **cpy,t_cmd *last);
char	*ft_string_handle_2(char *line, char *modified_line);




//__________________________________________ft_struct_manager_utils____________________________________

int	ft_lstsize_(t_word_list *lst);
t_word_list	*ft_lstlast_(t_word_list *lst);
int	ft_check_token_size(char *token_line);





char	*ft_duplineenv(t_env *env, char *variable);






void free_all(t_cmd *cmd);
void free_cpyenv(t_env *cpyenv);

void ft_shlvl(char **env);
char **newenv_child(t_env *env);









int	ft_check_words_list(t_word_list *tokens);
int	ft_lexer_analysis(t_word_list *words_list, t_bash *bash, char *new_string);










void print_dancing_penguin_frame1();





int return_intout(t_cmd *cmd,t_bash *bash_boss);


#endif