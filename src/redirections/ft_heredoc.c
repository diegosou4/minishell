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

void	ft_putforwe(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

t_file_struct	*get_file_num(void)
{
	static t_file_struct	instance;

	return (&instance);
}

static void	child_heredoc(char *delimiter, t_bash *bash_boss, int out, t_cmd *cmd)
{
	t_line	line;

	close_myhereprev(cmd);
	while (1)
	{
		ft_signal_manager_here();
		ft_line_handler(&line, bash_boss->cpyenv, HERE);
		get_file_num()->line = &line;
		if (ft_strcmp(delimiter, line.line) == 0 || !line.line)
		{
			printf("======================---------------------------------------- this is free \n");
			// ft_free_cmd_structure(bash_boss->commands);
		    // ft_free_exit_status(bash_boss->line, bash_boss->cpyenv, bash_boss->env);
			close(out);
			//exit(EXIT_SUCCESS);
			printf("%i meu PID NO FILHO \n", getpid());
			ft_exit(bash_boss->commands,&bash_boss->cpyenv);
			t_env *env;

			env = bash_boss->cpyenv;

			while(env != NULL)
			{
				if(env->value)
					printf("Valor %s\n",env->value);
				if(env->key)
					printf("Valor %s\n",env->key);
				env = env->next;
			}
			break;
		}
		else
		{
			ft_putforwe(line.line, out);
		}
		ft_free_line_struct(&line);
	}
	close(out);
	ft_exit(bash_boss->commands, &bash_boss->cpyenv);
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
		printf("======================---------------------------------------- this is hello \n");
		child_heredoc(delimiter, bash_boss, pipesfd[1], cmd);
		printf("======================---------------------------------------- this is Bye \n");
		//TODO no entra en esta seccion.
		// ft_exit(bash_boss->commands, &bash_boss->cpyenv);
		// ft_free_double_pointers(bash_boss->env);
		// freedouble_malloc(bash_boss->env,len_darray(bash_boss->env));
		// ft_free_exit_status(bash_boss->line, bash_boss->cpyenv, bash_boss->env);
		// ft_free_cmd_structure(bash_boss->commands);
	// ft_exit(bash_boss->commands, &bash_boss->cpyenv);
	}
	waitpid(pid, &exit_cod, 0);
	get_file_num()->exit_code = (exit_cod & 0xff00) >> 8;
	close(pipesfd[1]);
	return (pipesfd[0]);
}
