#include "minishell.h"

void	save_stdout(t_main *shell)
{
	shell->out = dup(STDOUT_FILENO);
	if (shell->out == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to save original stdout");
		exit(EXIT_FAILURE);
	}
}

void	save_stdin(t_main *shell)
{
	shell->in = dup(STDIN_FILENO);
	if (shell->in == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to save original stdin");
		exit(EXIT_FAILURE);
	}
}

void restore_stdout(t_main *shell)
{
	ft_printf("Here\n");
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
		ft_fprintf(STDERR_FILENO, "Failed to restore original stdin");
		exit(EXIT_FAILURE);
	}
	if (close(shell->in) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to close saved stdin");
		exit(EXIT_FAILURE);
	}
	if (close(redirected_fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to close redirected fd");
		exit(EXIT_FAILURE);
	}
}

int	redirect_output_builtin(t_files *outfile, t_main *shell)
{
	int	fd;

	save_stdout(shell);
	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "Failed to open output file");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2\n");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to close outfile fd");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	redirect_heredoc_builtin(t_files *infile)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Pipe heredoc\n");
		exit(EXIT_FAILURE);
	}
	ft_fprintf(fds[1], "%s", infile->file_name);
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Closing write end pipe heredoc");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2 heredoc stdin\n");
		exit(EXIT_FAILURE);
	}
	return (fds[0]);
}

int	redirect_input_builtin(t_files *infile, t_main *shell)
{
	int	fd;

	save_stdin(shell);
	if (infile->type == HEREDOC_END)
		return (redirect_heredoc_builtin(infile));
	fd = open(infile->file_name, O_RDONLY);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "Failed to open input file");
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
