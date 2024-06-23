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

void	handle_zero(void)
{
	ft_fprintf(2, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_one(void)
{

}

void	handle_two(pid_t to_kill)
{
	ft_fprintf(2, "\n");
	if (to_kill > 0)
		kill(to_kill, SIGINT);
}


void	sigint_main(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	if (g_signal_received == 0)
		handle_zero();
	else if (g_signal_received == 1)
		handle_one();
	else if (g_signal_received == 2)
		handle_two(to_kill);
	pid_for_signal(&to_restore);

}

void	handle_sigpipe(int signum)
{
	(void) signum;
}

void	subshell_handle(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	ft_fprintf(2, "\n");
	if (to_kill > 0)
		kill(to_kill, SIGINT);
	pid_for_signal(&to_restore);
}

void	signal_daddy(t_main *shell)
{
	struct sigaction	s;
	int	shlvl;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	shlvl = ft_atoi(get_env(&shell->env, "SHLVL"));
	if (shlvl <= 2)
	{
		s.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &s, NULL);
		s.sa_handler = sigint_main;
		sigaction(SIGINT, &s, NULL);
		s.sa_handler = handle_sigpipe;
		sigaction(SIGPIPE, &s, NULL);
	}
	else
	{
		s.sa_handler = subshell_handle;
		sigaction(SIGQUIT, &s, NULL);
		s.sa_handler = SIG_DFL;
		sigaction(SIGINT, &s, NULL);
		s.sa_handler = SIG_DFL;
		sigaction(SIGPIPE, &s, NULL);
	}
}
