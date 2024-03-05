/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:59:54 by juan-pma          #+#    #+#             */
/*   Updated: 2024/02/21 09:05:41 by juan-pma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/mini.h"

/*
    Arquivo principal responsável pelo fluxo de execução do programa shell.
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

int main(int ac,char **av,char **env)
{
    t_env *cpyenv;
    cpyenv = ft_nenv(env,1);
    t_redir *redir;  

    ft_handle_redir_input("OLA");

    //ft_env(cpyenv);

    char *args[] ={"ls","-l", NULL};
    t_cmd *test;
    test = ft_calloc(sizeof(t_cmd),1);
    test->path = ft_strdup("usr/bin/ls");
    test->literal = FALSE;
    test->fint_variable = FALSE;
    test->args = args;
    test->redir = NULL;
    redir = ft_calloc(sizeof(t_redir),1);

    redir->path = "EOF";
    redir->token = 3;
    redir->fd = -1;
    redir->next = NULL;
    test->redir = redir;

    execution(test,&cpyenv);
    ft_exp(cpyenv);*/  
   // ft_env(cpyenv);
}
