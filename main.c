/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-pma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:59:54 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/06 10:50:01 by diegmore         ###   ########.fr       */
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
    t_cmd *commands;
    t_redir *redir;
    t_redir *last;

    char *a1[] = {"cat", NULL};
    commands = malloc(sizeof(t_cmd));

    commands->path = ft_strdup("/bin/cat");
    commands->args = a1;
    commands->redir = NULL;
    commands->next = NULL;

    redir = malloc(sizeof(t_redir));

    redir->path = ft_strdup("file1.txt");
    redir->fd = -1;
    redir->token = redir_out;
    redir->next = NULL;

    last = malloc(sizeof(t_redir));

    last->path = ft_strdup("file3.txt");
    last->fd = -1;
    last->token = redir_in;
    last->next = NULL;

   // redir->next = last;
    commands->redir = last;
    start_exection(&commands,env,&cpyenv);

    /*
    char *a1[] = {"pwd", NULL};
    commands = malloc(sizeof(t_cmd));

    commands->path = ft_strdup("pwd");
    commands->args = a1;
    commands->redir = NULL;
    commands->next = NULL;

    t_cmd *c1;
    c1 = malloc(sizeof(t_cmd) * 1);

    c1->path = ft_strdup("/bin/cat");
    char *a2[] = {"cat", "-e", NULL};
    c1->args = a2;
    c1->redir = NULL;
    c1->next = NULL;

    commands->next = c1;

    */
    int pipes = ft_howpipes(commands);
    for (int i = 0; i < pipes; i++) {
        wait(NULL);
    }

    return(0);
}
