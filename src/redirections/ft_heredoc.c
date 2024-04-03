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

t_file_struct *get_file_num()
{
	static t_file_struct instance;
	return(&instance);
}
static void close_here(t_redir *fdclose)
{
    t_redir *ptr;

    ptr = fdclose;

    while(ptr != NULL)
    {
        if(ptr->fd != -1)
            close(ptr->fd);
        ptr = ptr->next;
    }

}

void ft_heredoc(char *delimiter, int in, int out,t_redir *fdclose)
{
    char *line;
    char *line_text;
    int pid;
    int exit_cod;

    pid = fork();
    get_file_num()->in = in;
    get_file_num()->out = out;
    get_file_num()->exit_code = 0;
    signal(SIGINT, SIG_IGN);
    if(pid == 0)
    {
        signal(SIGINT, handle_signal_here_doc);
        close_here(fdclose);
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
    waitpid(pid,&exit_cod,0);
    get_file_num()->exit_code = (exit_cod & 0xff00) >> 8;
    signal(SIGINT,handle_signal );
    close(out);
}



