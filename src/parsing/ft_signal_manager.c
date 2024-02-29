#include "../../includes/mini.h"

static void ft_putstr(char *line)
{
	while (*line)
	{
		write(1, line, 1);
		line++;
	}
}
void handle_signal(int signal1)
{
	if (signal1 == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else if (signal1 == SIGQUIT)
		ft_putstr("");
	else if (signal1 == SIGCHLD)
		ft_putstr("Child process terminated\n");
}

void ft_signal_manager()
{
	struct sigaction sa;

	sa.sa_handler = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL); // Handle Ctrl+C
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGCHLD, &sa, NULL); // Handle child process termination
}