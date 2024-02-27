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
// Define a global flag to indicate if the prompt has been printed
/*
	This function will create an array
	of structures, that will contain all the
	tokens already Trimmed.

	1. Args = the comand line.
	2. Output a list of tokens, to create

*/

int ft_flag(char *word)
{
	int flag;

	flag = 0;
	if (ft_strcmp(word, ">>") == 0)
		flag = 1;
	else if (ft_strcmp(word, "<<") == 0)
		flag = 2;
	else if (ft_strcmp(word, "<") == 0)
		flag = 3;
	else if (ft_strcmp(word, ">") == 0)
		flag = 4;

	return (flag);
}
t_word_desc *create_word_desc(char *word, int flag)
{
	t_word_desc *new_word = malloc(sizeof(t_word_desc));
	char *word_copy;

	word_copy = word;
	ft_checker_quotes(word_copy);
	new_word->word = ft_strdup(word_copy);
	printf("------------> this is the word :%s:\n", new_word->word);
	new_word->flags = flag;
	return (new_word);
}

t_word_list *create_word_node(t_word_desc *word)
{
	t_word_list *new_node = malloc(sizeof(t_word_list));
	new_node->word = word;
	new_node->next = NULL;
	return new_node;
}

static t_word_list *tokenize_and_print(char *token)
{
	char *subtoken;
	t_word_desc *word_desc;
	t_word_list *node;
	t_word_list *head = NULL;
	t_word_list *current_token = NULL;

	if (!token || !token[0])
		return NULL;

	subtoken = ft_strtok(token, "2"); // Tokenize the token with space
	while (subtoken != NULL)
	{
		if (subtoken[0] != '\0')
		{
			word_desc = create_word_desc(subtoken, ft_flag(subtoken));
			node = create_word_node(word_desc);
			// printf("this is the token: %s\n", subtoken);
			if (head == NULL)
			{
				head = node;
				current_token = node;
			}
			else
			{
				current_token->next = node;
				current_token = node;
			}
		}
		subtoken = ft_strtok(NULL, "2"); // Continue tokenizing with space
	}
	return (head);
}
/*
	🚩 check this function as we are alocating
	memmory here.
	- I need to free the list in case somenthing happend.
*/


t_word_list **ft_tokenizer_manager(char *line, char **env)
{
	char **tokens;
	t_word_list **words_list;
	char **current_token;
	int i;

	i = -1;
	if (env)
		;
	words_list = ft_calloc(100, sizeof(t_word_list *));
	tokens = ft_split(ft_create_string(line, env), '3');
	if (!tokens)
		return (NULL);
	ft_print_doble_char(tokens);
	if (tokens == NULL)
	{
		printf("No tokens found\n");
		return NULL;
	}
	current_token = tokens;
	while (*current_token != NULL)
	{
		words_list[++i] = tokenize_and_print(*current_token);
		current_token++;
	}

	i = -1;
	while (words_list[++i])
	{
		if (ft_check_valid_redir(words_list[i]) == 0)
			return (NULL);
	}
	i = -1;
	while (words_list[++i])
	{
		ft_print_list_struct(words_list[i]);
	}

	return (words_list);
}
/*
	🚩 check this function as we are alocating
	memmory here.
*/

void *ft_parse_manager(char **env)
{
	char *line;
	char **cpyenv;
	char *usr;
	char *line_text;

	ft_signal_manager();

	cpyenv = ft_arrcpy(env);
	// printf("/%s \n", pwd);
	while (1)
	{
		usr = ft_getenv(cpyenv, "USER", TRUE);
		line_text = ft_strjoin(ANSI_COLOR_CYAN, usr);						// Change color to cyan
		line_text = ft_strjoin(line_text, " @🐧shell:$ " ANSI_COLOR_RESET); // Reset color after prompt
		line = readline(line_text);
		if (!line || (ft_strcmp(line, "exit") == 0))
			break;
		if (ft_whitespace(line) == 1)
			add_history(line);
		if (ft_check_input(line))
			ft_tokenizer_manager(line, cpyenv);
		free(line);
	}
	return (NULL);
}