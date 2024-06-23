#include "minishell.h"

void	save_stdout(t_main *shell)
{
	shell->out = dup(STDOUT_FILENO);
	if (shell->out == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to save original stdout\n");
		exit(EXIT_FAILURE);
	}
}

void	save_stdin(t_main *shell)
{
	shell->in = dup(STDIN_FILENO);
	if (shell->in == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to save original stdin\n");
		exit(EXIT_FAILURE);
	}
}

void restore_stdout(t_main *shell)
{
	if (shell->out != STDOUT_FILENO)
	{
		if (dup2(shell->out, STDOUT_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Failed to restore original stdout\n");
			exit(EXIT_FAILURE);
		}
		if (close(shell->out) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Failed to close saved stdout\n");
			exit(EXIT_FAILURE);
		}
		shell->out = STDOUT_FILENO;
	}
}

void restore_stdin(t_main *shell, int redirected_fd)
{
	if (dup2(shell->in, STDIN_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to restore original stdin\n");
		exit(EXIT_FAILURE);
	}
	if (close(shell->in) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to close saved stdin\n");
		exit(EXIT_FAILURE);
	}
	if (redirected_fd != -1)
	{
		if (close(redirected_fd) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Failed to close redirected fd\n");
			exit(EXIT_FAILURE);
		}
	}
}
