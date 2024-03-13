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
    t_cmd *second;
    t_cmd *last;
    t_redir *redirf;

    redirf = malloc(sizeof(t_redir) * 1);

    redirf->path = ft_strdup("file1.txt");
    redirf->token = 1;
    redirf->fd = -1;
    redirf->next = NULL;
    // Second

    second = malloc(sizeof(t_cmd) * 1);
    second->path = ft_strdup("/bin/ls");
    char *a2[] = {"ls", "-l", NULL};
    second->args = a2;
    second->redir = NULL;
    second->next = NULL;

  

    // Comands  
    commands = malloc(sizeof(t_cmd) * 1);
    commands->path = ft_strdup("/bin/cat");
    char *a1[] = {"cat","-e", NULL};
    commands->args = a1;
    commands->redir = NULL;
    commands->next = NULL;

    commands->redir = redirf;
    second->next = commands;


    start_exection(&second,env,&cpyenv);

    close(redirf->fd);


    return(0);
}
