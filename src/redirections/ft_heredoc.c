/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:43:29 by diegmore          #+#    #+#             */
/*   Updated: 2024/02/28 16:43:30 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void ft_putforwe(char *line,int fd)
{
    ft_putstr_fd(line,fd);
    ft_putchar_fd('\n',fd);
    free(line);
}
/*
int ft_handle_redir_input(char *delimiter)
{

    int fd;

    fd = ft_heredoc(delimiter);
    char *str;
    str = get_next_line(fd);
    while(str != NULL)
    {
        printf("%s",str);
        str = get_next_line(fd);    
    }
    close(fd);
    return(0);

}*/


void ft_heredoc(char *delimiter, int in, int out, t_bash *bash_boss)
{
    char *line;
    char *line_text;
    int pid;
    pid = fork();
    if(pid == 0)
    {
        if(bash_boss->pipein != - 1)
            close(bash_boss->pipein);
        if(bash_boss->pipeout != -1)
            close(bash_boss->pipeout);
        while(1)
        {
            line_text = ft_strjoin(ANSI_COLOR_PURPLE,"🐧🐧heredoco>");
            line = readline(line_text);  
            free(line_text);
            if(strncmp(delimiter,line,ft_strlen(line)) == 0)
            {
                free(line);
                close(out);
                close(in);
                exit(EXIT_SUCCESS);
            }
            else
                ft_putforwe(line,out);
            }
    }
    waitpid(pid,&pid,0);
    close(out);
}


void case_heredoc(t_cmd *ptrcmd)
{
    if(ptrcmd->args[0] == NULL && ptrcmd->redir != NULL)
    {   
    //Da free nas coisas
    //
        exit(EXIT_SUCCESS);
    }




}