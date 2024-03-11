/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:27:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/03/07 12:27:15 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini.h"


int ft_countpipes(t_cmd *cmd)
{
    int i;
    i = 0;
    t_cmd *ptr;

    ptr = cmd;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return(i);
}


void open_pipes(t_cmd **cmd)
{
    t_cmd *ptr;
    ptr = (*cmd);
    while(ptr != NULL)
    {
        pipe(ptr->pipesfd);
        ptr = ptr->next;
    }
}

void executor_without(t_cmd *commands, char **env, int in,int out,t_env **cpy)
{
    int pid;

    pid = fork();
    if(pid == 0)
    {
        dup2(in, 0);
        dup2(out,1);
        if(in != 0)
            close(in);
        if(out != 1)
            close(out);
        if(check_builtings(commands) == 0)
            execve(commands->path,commands->args,env);
        else
        {
            execution(commands,cpy);
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
    if(out != 1)
        close(out);
    if(in != 0)
        close(in);
}
/*
void execute_simple(t_cmd **cmd,char **env,t_env **cpy)
{
    if(env == NULL)
        return;





}*/

// MEU PARCEIRO BOLADAO VOCE E O CARA
// QUE QUE TU TEM QUE FAZER
// ABRE OS PIPES DOS COMANDOS NA HUMILDADE
// VERIFICA SE HA ALGUMA REDIRECAP
// DEPOIS DE QUEBRADA VAI PEGAR O ULTIMO REDIRECT DELE
// SENDO IN OU OUT
// O RESTO VAI SER IGNORADO SE TA LIGADO NE!!
// ENTAO VAMO PENSAR BEM 
// SE TU TIVER IN E OUT METE MARCHA E SO FAZ ACONTECER
// A GENTE VAI TER UM WHILE 
// TEMOS QUE IDENTIFICAR SE ESTAMOS NA PRIMEIRA EXECUCAO 
// POR QUE SE NAO TIVEMOS IN NA PRIMEIRA EXECUCAO VAMOS USAR O 0
// E NA ULTIMA SE NAO TIVEMOS OUT VAMOS IMPRIMIR NO 1


// COMECO



// MEIO



// E FIM

void ft_magane_executor(t_cmd **cmd, char **env,t_env **cpy)
{
    t_cmd *ptr;
    t_cmd *last;
    ptr = (*cmd);
    
    open_pipes(cmd);
    if(check_all(ptr->redir) > 0)
    {
        executor_redir(cmd,env,cpy);
    }
    /*
    if(index == 0)
        executor_without(ptr, env, 0 , ptr->pipesfd[1],cpy);
    last = ptr;
    ptr = ptr->next;
    while(ptr->next != NULL)
    {
        if(check_out(last->redir) == 0 && check_out(ptr->redir) == 0)
            executor_without(ptr,env,last->pipesfd[0],ptr->pipesfd[1],cpy);
        last = ptr;
        ptr = ptr->next;
    }
    if(check_out(last->redir) == 0 && check_out(ptr->redir) == 0)
        executor_without(ptr,env,last->pipesfd[0],1,cpy);
    */
}



void open_redi(int token,t_redir **redir)
{

    if(token == 1)
        (*redir)->fd = open((*redir)->path,O_WRONLY | O_CREAT | O_TRUNC, 0664);
    else if(token == 2)
    {
        (*redir)->fd = open((*redir)->path,O_RDONLY , 0777);
        if(access((*redir)->path,R_OK) == 0)
            return;
        else
        {
            perror("Error");
            return;
        }
    }
        
}

int ft_howpipes(t_cmd *comands)
{
    int i;
    i = 0;

    t_cmd *ptr;
    ptr = comands;
    while(ptr != NULL)
    {
        ptr = ptr->next;
        i++;
    }
    return(i);

}

void start_exection(t_cmd **commands,char **env,t_env **cpy)
{
    t_cmd *ptr;
    ptr = (*commands);
    t_redir *redptr;
    while(ptr != NULL)
    {
        redptr = ptr->redir;
        while(redptr != NULL)
        {
            open_redi(redptr->token,&redptr);
            redptr = redptr->next;
        }
        ptr = ptr->next;
    }
    ft_magane_executor(commands,env,cpy);
    ft_close(commands);
}