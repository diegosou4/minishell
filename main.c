/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:59:54 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/18 14:27:53 by marvin           ###   ########.fr       */
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

t_word_list	**ft_tokenizer_manager(char *line, t_env *env)
{
	char		**tokens;
	t_word_list	**words_list;
	char *new_string;
	int			i;

	i = -1;
	new_string = ft_create_string(line);
	words_list = (t_word_list **)ft_calloc(100, sizeof(t_word_list *));
	tokens = ft_split(new_string, '3');
	if (!tokens)
	{
		free(words_list);
		free(new_string);
		return (NULL);
	}
	while (tokens[++i] != NULL)
	{
		words_list[i] = tokenize_and_print(tokens[i]);
	}
	ft_free_double_pointers(tokens);
	i = -1;
	while (words_list[++i])
	{
		ft_extract_var(words_list[i], env);
		ft_flags_tags_assignment(words_list[i]);
		if (ft_check_words_list(words_list[i]) == 1)
			words_list[i]->redirection = TRUE;
		else
			words_list[i]->redirection = FALSE;
		ft_quotes_remove(words_list[i]);
		if (ft_check_valid_redir(words_list[i]) == 0)
		{
			ft_free_double_word_list(words_list);
			free(new_string);
			return (NULL);
		}
		// ft_print_list_struct(words_list[i], i);
	}
	free(new_string);
	return (words_list);
}
/*
	🚩 check this function as we are alocating
	memmory here.
*/

void	*ft_parse_manager(char **env)
{
	t_line	line;
	t_env	*cpyenv;
	t_cmd *cmd_structure;

	ft_signal_manager();
	cpyenv = ft_nenv(env);
	while (1)
	{
		ft_line_handler(&line, cpyenv);
		line.line = readline(line.line_text);
		if (!line.line || (ft_strcmp(line.line, "exit") == 0))
		{
			ft_free_line_struct(&line);
			ft_free_env_list(cpyenv);
			break ;
		}
		if (ft_whitespace(line.line) == 1)
			add_history(line.line);
		if (ft_check_input(line.line))
		{
			cmd_structure = ft_structure_creation(line.line, cpyenv);
			ft_free_cmd_structure(cmd_structure);
		}
		ft_free_line_struct(&line);
		free(line.line);
	}
	return NULL;
}

int	main(int argc, char *argv[], char **env)
{
	if (argc == 1 && argv[0])
		ft_parse_manager(env);
}
