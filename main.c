/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:53:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/19 11:53:35 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mini.h"

/*
Arquivo principal responsável pelo fluxo de execução do
programa shell.
O programa segue os seguintes passos:
1. Ler Entrada: O usuário insere a linha de entrada.
2. Gerenciador de Análise: A linha de entrada é passada para o gerenciador de
análise para lidar com erros de análise.
3. Verificar Entrada: O gerenciador de análise chama a função para verificar a
linha de entrada em busca de erros.
4. Criar String: Se a entrada for válida, a string é criada.
5. Manipular String: Manipulação da string para remover quaisquer erros.
6. Criar Tokens: Criação de tokens a partir da string.
7. Criar Estrutura: Criação da estrutura para armazenar tokens e outras
informações relevantes.
*/

int ft_check_words_list(t_word_list *tokens)
{
	while (tokens)
	{
		if (tokens->word->tags == EXCECUTOR)
			return 1;
		tokens = tokens->next;
	}
	return (0);
}
int ft_lexer_analysis(t_word_list *words_list, t_env *env, char *new_string)
{
	ft_extract_var(words_list, env);
	ft_flags_tags_assignment(words_list);
	if (ft_check_words_list(words_list) == 1)
		words_list->redirection = TRUE;
	else
		words_list->redirection = FALSE;
	ft_quotes_remove(words_list);
	if (ft_check_valid_redir(words_list) == 0)
	{
		free(new_string);
		return (0);
	}
	return (1);
}

void ft_free_wd_list_char(t_word_list **word_list, char *new_string)
{
		free(word_list);
		free(new_string);
}
t_word_list	**ft_tokenizer_manager(char *line, t_env *env)
{
	t_word_list	**words_list;
	char		**tokens;
	char 		*new_string;
	int			i;

	i = -1;
	new_string = ft_create_string(line);
	words_list = (t_word_list **)ft_calloc(100, sizeof(t_word_list *));
	tokens = ft_split(new_string, '3');
	if (!tokens)
	{
		ft_free_wd_list_char(words_list, new_string);
		return (NULL);
	}
	while (tokens[++i] != NULL)
		words_list[i] = tokenize_and_print(tokens[i]);
	i = -1;
	while (words_list[++i])
		if (!ft_lexer_analysis(words_list[i], env, new_string))
		{
			ft_free_double_word_list(words_list);
			return (NULL);
		}
	ft_free_tokens_new_string(tokens, new_string);
	return (words_list);
}
/*
	🚩 check this function as we are alocating
	memmory here.
*/

t_cmd *ft_structure_manager(t_line *line, t_env *cpyenv)
{
	t_word_list **list;
	t_cmd *cmd_structure;
	list = ft_tokenizer_manager(line->line, cpyenv);
	cmd_structure = ft_structure_creation(list);
//	ft_free_double_word_list(list);
	return(cmd_structure);
}
void	*ft_parse_manager(char **env)
{
	t_line	line;
	t_bash bash_boss;

	ft_signal_manager();
	bash_boss.env = ft_arrcpy(env);
	bash_boss.cpyenv = ft_nenv(env,1);
	while (1)
	{
		ft_line_handler(&line, bash_boss.cpyenv);
		line.line = readline(line.line_text);
		if (!line.line || (ft_strcmp(line.line, "exit") == 0))
		{
			ft_free_line_env(&line, bash_boss.cpyenv);
			break ;
		}
		if (ft_whitespace(line.line) == 1)
			add_history(line.line);
		if (ft_check_input(line.line))
		{
			bash_boss.commands = ft_structure_manager(&line, bash_boss.cpyenv);
			start_execution(bash_boss);
		}
		ft_free_line_struct(&line);
	}
	return NULL;
}

int	main(int argc, char *argv[], char **env)
{
	// env[0] = NULL;
	if (argc == 1 && argv[0])
		ft_parse_manager(env);
}
