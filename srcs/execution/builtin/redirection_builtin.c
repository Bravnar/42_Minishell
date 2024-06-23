#include "minishell.h"

int	redirect_output_builtin(t_files *outfile, t_main *shell)
{
	int	fd;

	save_stdout(shell);
	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "Failed to open output file\n");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2\n");
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Failed to close outfile fd\n");
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

void	redir_builtin(t_cmds *cmds, t_main *shell, t_stds *fd_stds, t_exec code)
{
	if (code == SINGLE || code == FIRST)
	{
		if (cmds->last_infile)
			fd_stds->in = redirect_input_builtin(cmds->last_infile, shell);
	}
	else
	{
		if (cmds->last_infile)
			redirect_input_builtin(cmds->last_infile, shell);
	}
	if (code == LAST)
	{
		if (cmds->last_outfile)
			fd_stds->out = redirect_output_builtin(cmds->last_outfile, shell);
	}
	else
	{
		if (cmds->last_outfile)
			redirect_output_builtin(cmds->last_outfile, shell);
	}
}
