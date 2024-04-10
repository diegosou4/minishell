/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:43:29 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/08 11:21:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_putforwe(char *line, int fd)
{
	char *str;
	int len;

	str = ft_strdup(line);
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	free(str);
	return(len);
}

t_file_struct	*get_file_num(void)
{
	static t_file_struct	instance;

	return (&instance);
}
static void badsignal_here(t_bash *bash_boss, int count, char *delimiter)
{
	char *str;
	str = ft_itoa(count);
	ft_putstr_fd("minishell warning: here-document at line ",2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" by end-of-file (wanted `",2);
	ft_putstr_fd(delimiter,2);
	ft_putstr_fd("')\n",2);
	if(str != NULL)
		free(str);
}


static void	child_heredoc(char *delimiter, t_bash *bash_boss, int out, t_cmd *cmd)
{
	t_line	line;
	int count;
	count = 0;

	close_myhereprev(cmd);
	while (1)
	{
		ft_signal_manager_here();
		ft_line_handler(&line, bash_boss->cpyenv, HERE);
		get_file_num()->line = &line;
		if (ft_strcmp(delimiter, line.line) == 0 || !line.line)
		{
			if(!line.line)
				badsignal_here(bash_boss,count,delimiter);
			break;
		}
		else
			count += ft_putforwe(line.line, out);
		free(line.line);
	}
	if(line.line != NULL)
		free(line.line);
	free_here(bash_boss);
	close(out);
	exit(EXIT_SUCCESS);
}

int	ft_heredoc(char *delimiter, t_bash *bash_boss, t_cmd *cmd)
{
	int	pid;
	int	exit_cod;
	int	pipesfd[2];

	pipe(pipesfd);
	pid = fork();
	get_file_num()->in = pipesfd[0];
	get_file_num()->out = pipesfd[1];
	get_file_num()->exit_code = 0;
	if (pid == 0)
	{
		close(pipesfd[0]);
		child_heredoc(delimiter, bash_boss, pipesfd[1], cmd);
		ft_exit(bash_boss->commands);
	}
	waitpid(pid, &exit_cod, 0);
	get_file_num()->exit_code = (exit_cod & 0xff00) >> 8;
	close(pipesfd[1]);
	return (pipesfd[0]);
}
