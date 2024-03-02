/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:42:35 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/02 15:53:00 by juan-pma         ###   ########.fr       */
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

t_tags	ft_tags(t_word_desc *word)
{
	char	*word_cpy;
	int		len;

	word_cpy = word->word;
	len = ft_strlen(word_cpy);
	if ((word_cpy[0] == '\'' && word_cpy[len - 1] == '\''))
		return (WORD);
	else if ((word_cpy[0] == '\"' && word_cpy[len - 1] == '\"'))
		return (SPECIAL_VAR);
	else if (word->flags == 1 || word->flags == 2 
		|| word->flags == 3 || word->flags == 4)
	{
		return (EXCECUTOR); 
	}
	else if (word->word[0] == '$')
		return (VARIABLE);
	else if (ft_strcmp(word_cpy, "$?") == 0)
		return (SPECIAL_PAR);
	else
		return (WORD);
}

int	ft_flag(char *word)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(word, ">>") == 0)
		flag = 1;
	else if (ft_strcmp(word, "<<") == 0)
		flag = 2;
	else if (ft_strcmp(word, "<") == 0)
		flag = 3;
	else if (ft_strcmp(word, ">") == 0)
		flag = 4;
	else if (ft_strcmp(word, "<>") == 0)
		flag = 5;
	return (flag);
}

t_word_desc	*create_word_desc(char *word, int flag)
{
	t_word_desc	*new_word;
	char		*word_copy;

	new_word = malloc(sizeof(t_word_desc));
	word_copy = word;
	new_word->word = ft_strdup(word_copy);
	new_word->flags = flag;
	new_word->tags = ft_tags(new_word);
	return (new_word);
}

t_word_list	*create_word_node(t_word_desc *word)
{
	t_word_list	*new_node;

	new_node = malloc(sizeof(t_word_list));
	new_node->word = word;
	new_node->next = NULL;
	return (new_node);
}

static t_word_list	*tokenize_and_print(char *token)
{
	char		*subtoken;
	t_word_desc	*word_desc;
	t_word_list	*node;
	t_word_list	*head;
	t_word_list	*current_token;

	current_token = NULL;
	head = NULL;
	if (!token || !token[0])
		return (NULL);
	subtoken = ft_strtok(token, "2");
	while (subtoken != NULL)
	{
		if (subtoken[0] != '\0')
		{
			word_desc = create_word_desc(subtoken, ft_flag(subtoken));
			node = create_word_node(word_desc);
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
		subtoken = ft_strtok(NULL, "2");
	}
	return (head);
}
/*
	🚩 check this function as we are alocating
	memmory here.
	- I need to free the list in case somenthing happend.
*/

t_word_list	**ft_tokenizer_manager(char *line, t_env *env)
{
	char		**tokens;
	t_word_list	**words_list;
	int			i;

	i = -1;
	words_list = ft_calloc(100, sizeof(t_word_list *));
	tokens = ft_split(ft_create_string(line), '3');
	if (!tokens)
		return (NULL);
	while (tokens[++i] != NULL)
		words_list[i] = tokenize_and_print(tokens[i]);
	i = -1;
	while (words_list[++i])
	{
		if (ft_check_valid_redir(words_list[i]) == 0)
		{
			ft_free_double_pointers(tokens);
			return (NULL);
		}
	}
	i = -1;
	while (words_list[++i])
	{
		ft_extract_var(words_list[i], env);
		ft_quotes_remove(words_list[i]);
		ft_print_list_struct(words_list[i]);
	}
	ft_free_double_pointers(tokens);
	return (words_list);
}
/*
	🚩 check this function as we are alocating
	memmory here.
*/

void	*ft_parse_manager(char **env)
{
	char	*line;
	char	*usr;
	char	*line_text;
	char	*color_line;
	t_env	*cpyenv;
	int	index;
	char	*value;

	ft_signal_manager();
	cpyenv = ft_nenv(env);
	while (1)
	{
		value = ft_path_handler(cpyenv, "USER");
		color_line = ft_strjoin(ANSI_COLOR_CYAN, (value));
		line_text = ft_strjoin(color_line, "@🐧shell:$ " ANSI_COLOR_RESET);
		line = readline(line_text);
		if (!line || (ft_strcmp(line, "exit") == 0))
		{
			free(line_text);
			free(color_line);
			ft_free_env_list(cpyenv);
			break ;
		}
		if (ft_whitespace(line) == 1)
			add_history(line);
		if (ft_check_input(line))
			ft_tokenizer_manager(line, cpyenv);
		free(color_line);
		free(line_text);
		free(line);
	}
	return (NULL);
}
