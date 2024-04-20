/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:53:34 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/20 12:18:11 by diegmore         ###   ########.fr       */
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

int	ft_list_creation(t_word_list **words_list, t_bash *bash, char **tokens,
		char *new_string)
{
	int	i;

	i = -1;
	while (words_list[++i])
	{
		if (!ft_lexer_analysis(words_list[i], bash, new_string))
		{
			ft_free_list_tokens(words_list, tokens, NULL, bash);
			return (0);
		}
	}
	return (1);
}

t_word_list	**ft_tokenizer_manager(char *line, t_bash *bash)
{
	t_word_list	**words_list;
	char		**tokens;
	char		*new_string;
	int			i;

	i = -1;
	new_string = ft_create_string(line, bash);
	if (!new_string)
		return (NULL);
	tokens = ft_split(new_string, '\3');
	words_list = (t_word_list **)ft_calloc(ft_double_strlen(tokens) + 1,
			sizeof(t_word_list *));
	if (!tokens)
	{
		ft_free_list_tokens(words_list, tokens, new_string, NULL);
		return (NULL);
	}
	while (tokens[++i] != NULL)
		words_list[i] = tokenize_and_print(tokens[i]);
	i = -1;
	if (!ft_list_creation(words_list, bash, tokens, new_string))
		return (NULL);
	ft_free_tokens_new_string(tokens, new_string);
	return (words_list);
}
/*
	🚩 check this function as we are alocating
	memmory here.
*/

void	ft_structure_manager(t_line *line, t_bash *bash)
{
	t_word_list	**list;
	t_cmd		*cmd_structure;

	get_file_num()->bash = bash;
	bash->exit_status = get_file_num()->exit_code;
	list = ft_tokenizer_manager(line->line, bash);
	if (!list)
		return ;
	get_file_num()->list = list;
	cmd_structure = ft_structure_creation(list);
	bash->commands = cmd_structure;
	ft_free_double_word_list(list);
	if (bash->commands)
		start_execution(bash);
	bash->exit_status = get_file_num()->exit_code;
	ft_free_cmd_structure(cmd_structure);
}

void	*ft_parse_manager(char **env)
{
	t_line	line;
	t_bash	bash_boss;

	get_file_num()->exit_code = 0;
	ft_bash_boss_init(&bash_boss, env);
	while (1)
	{
		ft_signal_manager();
		ft_line_handler(&line, bash_boss.cpyenv, MAIN);
		bash_boss.line = &line;
		if (!line.line)
		{
			ft_free_exit_status(&line, bash_boss.cpyenv, bash_boss.env);
			break ;
		}
		if (ft_whitespace(line.line) == 1)
			add_history(line.line);
		if (ft_check_input(line.line, &bash_boss))
			ft_structure_manager(&line, &bash_boss);
		get_file_num()->exit_code = bash_boss.exit_status;
		ft_free_line_struct(&line);
	}
	rl_clear_history();
	return (NULL);
}

int	main(int argc, char *argv[], char **env)
{
	if (argc == 1 && argv[0])
		ft_parse_manager(env);
}
