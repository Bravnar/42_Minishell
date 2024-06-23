#include "minishell.h"

pid_t	pid_for_signal(pid_t *new)
{
	static pid_t	to_kill;

	if (new)
		to_kill = *new;
	return (to_kill);
}

void	sigint_handle(int signum)
{
	/* pid_t	child;
	pid_t	reset; */

	(void) signum;
}

void	handle_interactive(void)
{
	ft_fprintf(2,"\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_daddy(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = sigint_handle;
	sigaction(SIGINT, &sa, NULL);
}
