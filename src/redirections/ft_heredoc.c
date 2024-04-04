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

void	ft_putforwe(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	free(line);
}

t_file_struct	*get_file_num(void)
{
	static t_file_struct	instance;

	return (&instance);
}

static void	child_heredoc(char *delimiter, t_bash *bash_boss, int out, t_cmd *cmd)
{
	char	*line;
	char	*line_text;

	ft_signal_manager_here();
	close_myhereprev(cmd);
	printf(" meu pid %i", getpid());
	while (1)
	{
		line_text = ft_strjoin(ANSI_COLOR_PURPLE, "🐧🐧heredoco>");
		line = readline(line_text);
		free(line_text);
		if (ft_strncmp(delimiter, line, ft_strlen(line)) == 0 || !line)
		{
			free(line);
			close(out);
			ft_free_cmd_structure(bash_boss->commands);
			ft_free_double_word_list(bash_boss->list);
			exit(EXIT_SUCCESS);
		}
		else
		{
				ft_putforwe(line, out);
		}
	}
	close(out);
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
		freedouble_malloc(bash_boss->env,len_darray(bash_boss->env));
		ft_free_env_list(bash_boss->cpyenv);
		close(pipesfd[0]);
		child_heredoc(delimiter, bash_boss, pipesfd[1], cmd);
	}
	waitpid(pid, &exit_cod, 0);
	get_file_num()->exit_code = (exit_cod & 0xff00) >> 8;
	close(pipesfd[1]);	
	return (pipesfd[0]);
}
