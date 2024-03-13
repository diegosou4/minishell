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
    if(ptr->next != NULL)
    {
        while(ptr != NULL)
        {
            pipe(ptr->pipesfd);
            ptr = ptr->next;
        }
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


int return_heredoc(t_redir *redir)
{
    int i;
    t_redir *ptr;
    i = 0;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 3)
            return(1);
        ptr = ptr->next;
    }
    return(0);
}
int return_out(t_redir *redir)
{
    int fd;
    t_redir *ptr;
    fd = STDOUT_FILENO;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 1 || ptr->token == 4 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;
    }
    return(fd);
}

int return_in(t_redir *redir)
{
    int fd;
    t_redir *ptr;
    fd = STDIN_FILENO;
    ptr = redir;
    while(ptr != NULL)
    {
        if(ptr->token == 2 || ptr->token == 5)
            fd = ptr->fd;
        ptr = ptr->next;        
    }
    return(fd);
}


// Pipes abertos
// vamos criar o filho e meter marcha

void ft_magane_executor(t_cmd **cmd, char **env,t_env **cpy)
{
    int pid;
    t_cmd *ptrcmd;
    ptrcmd = (*cmd);
    open_pipes(cmd);
    pid = fork();
    // Dentro do filho
    // vamos chegar as redirecoes
    // vamos buscar o ultimo in file e out file
    // vamos fechar aquilo que nao precisamos para nao da leaks de fd
    int fdin;
    int fdout;
    fdin = STDIN_FILENO;
    fdout = STDOUT_FILENO;
    if(pid == 0)
    {
        if(return_heredoc((*cmd)->redir) == 0)
        {
            fdin = return_in((*cmd)->redir);
            fdout = return_out((*cmd)->redir);
            close((*cmd)->pipesfd[0]);
            close((*cmd)->pipesfd[1]);
        }else
        {
            fdin = (*cmd)->pipesfd[0];
                if(fdout == STDOUT_FILENO)
                    fdout = (*cmd)->pipesfd[1];
        }
        dup2(fdout,1);
        dup2(fdin,0);
        if(fdout != 1)
            close(fdout);
        if(fdin != 0)
            close(fdin);
        execve((*cmd)->path,(*cmd)->args,env);
    }
    closeredir((*cmd)->redir);

}


// Debito de Progamacao
// Voltar e tratar erros de abertura de arquivos

int redir_error(int fd)
{
    if(fd < 0)
        perror("Error ");
    return(0);
}



int open_redir(t_cmd **commands)
{
    t_cmd *ptrcmd;
    t_redir *ptrredir;

    ptrcmd = (*commands);
    while(ptrcmd != NULL)
    {
        ptrredir = ptrcmd->redir;
        while(ptrredir != NULL)
        {
        if(ptrredir->token == 1)
            ptrredir->fd = open(ptrredir->path,O_WRONLY | O_CREAT | O_TRUNC, 0664);
        else if(ptrredir->token == 2)
            ptrredir->fd = open(ptrredir->path,O_RDONLY , 0777);
        if(ptrredir->fd < 0)
            return(redir_error(ptrredir->fd));
        ptrredir = ptrredir->next;
    }
    ptrcmd = ptrcmd->next;
    }
    return(1);
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
    open_redir(commands);
    ft_magane_executor(commands,env,cpy);
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
}