/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:13:14 by juan-pma          #+#    #+#             */
/*   Updated: 2024/03/21 18:02:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

// static void	ft_putstr(char *line)
// {
// 	while (*line)
// 	{
// 		write(1, line, 1);
// 		line++;
// 	}
// }

void	handle_signal(int signal1)
{
	if (signal1 == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
