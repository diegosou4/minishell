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


int ft_heredoc(char *delimiter)
{
    int fd;
    char *line;
    char *line_text;

    fd = open(".temp.txt", O_TRUNC | O_CREAT | O_RDWR, 0777);
    if(fd < 0)
        return(fd);
    while(1)
    {
        line_text = ft_strjoin(ANSI_COLOR_PURPLE,"🐧🐧>");
        line = readline(line_text);
        free(line_text);
        if(strncmp(delimiter,line,ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        else
            ft_putforwe(line,fd);
    }
    close(fd);
    fd = open(".temp.txt", O_RDONLY, 0777);
    return(fd);
}
