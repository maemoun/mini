#include "main.h"

int	g_var = 0;

void	ft_change_global(int flag)
{
	g_var = flag;
}

void	ctlc_handler(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_var == 0)
		rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, ctlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
