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

}


int ft_heredoc(char *delimiter)
{
    int fd[2];
    char *line;
    char *line_text;
    pipe(fd);
    while(1)
    {
        line_text = ft_strjoin(ANSI_COLOR_PURPLE,"🐧🐧heredoco>");
        line = readline(line_text);  
        free(line_text);
        if(strncmp(delimiter,line,ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        else
            ft_putforwe(line,fd[1]);
    }
    close(fd[1]);
    return(fd[0]);
}


void case_heredoc(t_cmd *ptrcmd,t_bash *bash_boss)
{
    if(ptrcmd->args[0] == NULL && ptrcmd->redir != NULL)
    {   
    //Da free nas coisas
    //
        exit(EXIT_SUCCESS);
    }




}