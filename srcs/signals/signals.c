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
	ft_fprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_zero(void)
{
	int	err_code;

	err_code = 130;
	// ft_fprintf(2, "\n");
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	send_err_code(&err_code);
}

void	handle_one(void)
{
	write(STDERR_FILENO, "\n", 1);
	exit(130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoco(pid_t to_kill)
{
	int	err_code;

	err_code = 130;
	ft_fprintf(2, "\n");
	if (to_kill > 0)
		kill(to_kill, SIGINT);
	send_err_code(&err_code);
}

int	send_err_code(int *new_err)
{
	static int	err = 0;

	if (new_err)
	{
		err = *new_err;
	}
	return (err);
}

void	handle_two(pid_t to_kill)
{
	int	err_code;

	err_code = 130;
	ft_fprintf(2, "\n");
	if (to_kill > 0)
		kill(to_kill, SIGINT);
	send_err_code(&err_code);
}

void	sigint_main(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	if (g_signal_received == NORMAL)
		handle_zero();
	else if (g_signal_received == HEREDOC_SIG)
		handle_heredoco(to_kill);
	else if (g_signal_received == EXEC)
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

int	is_vscode_terminal(t_main *shell)
{
	char	*vscode_var;

	vscode_var = get_env(&shell->env, "TERM_PROGRAM");
	if (!vscode_var || vscode_var[0] == '\0')
		return (2);
	if (!ft_strcmp(vscode_var, "vscode"))
	{
		free(vscode_var);
		return (3);
	}
	else
	{
		free(vscode_var);
		return (2);
	}
}

void heredoc_sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    if (g_signal_received == HEREDOC_SIG)
    {
        exit(130);  // Exit the child process
    }
}

void setup_heredoc_signals(void)
{
    struct sigaction s;
    
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    s.sa_handler = heredoc_sigint_handler;
    sigaction(SIGINT, &s, NULL);
	s.sa_handler = heredoc_sigint_handler;
	sigaction(SIGQUIT, &s, NULL);
}

void	signal_daddy(t_main *shell)
{
	struct sigaction	s;
	int					shlvl;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	shlvl = ft_atoi(get_env(&shell->env, "SHLVL"));
	if (shlvl <= is_vscode_terminal(shell))
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
