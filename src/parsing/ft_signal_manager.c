/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:13:14 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/26 16:16:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	handle_signal(int signal1)
{
	if (signal1 == SIGINT)
	{
		write(0, "\n", 1);
		g_exit_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal_child(int signal1)
{
	if (signal1 == SIGINT)
	{
		write(1, "\n", 2);
		g_exit_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal1 == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		g_exit_status = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_signal_manager(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_signal_manager_child(void)
{
	signal(SIGINT, handle_signal_child);
    signal(SIGQUIT, handle_signal_child);
}

void	handle_signal_here_doc(int signal1)
{
    int in;
    int out;

    in = get_file_num()->in;
    out = get_file_num()->out;
	if (signal1 == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 130;
		if(in != -1)
        	close(in);
        if(out != -1)
			close(out);
		exit(127);
	}
}

void	ft_signal_manager_here(void)
{
	signal(SIGINT, handle_signal_here_doc);
	signal(SIGQUIT, SIG_IGN);
}