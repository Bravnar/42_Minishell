#include "minishell.h"

int exec_first_builtin(t_cmds *cmds, t_main *shell)
{
	int		fds[2];
	t_stds	fd_stds;

	save_stdout(shell);
	save_stdin(shell);
	fd_stds.in = -1;
	fd_stds.out = -1;
	if (pipe(fds) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Pipe\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Hello\n");
		exit(EXIT_FAILURE);
	}
	redir_builtin(cmds, shell, &fd_stds);
	builtins(cmds, shell, STDOUT_FILENO);
	close_first_parent(fds);
	if (cmds->last_infile)
		restore_stdin(shell, fd_stds.in);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (dup2(shell->out, STDOUT_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Dup2 shellout first builtin");
		exit(EXIT_FAILURE);
	}
	return (fds[0]);
}

int	exec_last_builtin(t_cmds *cmds, int fd_in, t_main *shell)
{
	t_stds	fd_stds;

	save_stdin(shell);
	if (cmds->last_infile && !cmds->prev->last_outfile && cmds->prev->cmd_grp)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Hello\n");
			exit(EXIT_FAILURE);
		}
	}
	redir_builtin(cmds, shell, &fd_stds);
	shell->err_code = builtins(cmds, shell, STDOUT_FILENO);
	close_fdin_builtin(fd_in);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (cmds->last_infile)
		restore_stdin(shell, -1);
	else
	{
		if (dup2(shell->in, STDIN_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "dup2 taking fd_in back %d\n", shell->in);
			exit(EXIT_FAILURE);
		}
	}
	return (-1);
}

int exec_middle_builtins(t_cmds *cmds, int fd_in, t_main *shell)
{
	int fds[2];
	t_stds fd_stds;

	fd_stds.in = -1;
	fd_stds.out = -1;
	save_stdin(shell);
	save_stdin(shell);
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	if (cmds->last_infile && !cmds->prev->last_outfile && cmds->prev->cmd_grp)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Issue dup2\n");
			exit(EXIT_FAILURE);
		}
	}
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	redir_builtin(cmds, shell, &fd_stds);
	shell->err_code = builtins(cmds, shell, STDOUT_FILENO);
	close_middle_parent(fds, fd_in);
	if (cmds->last_outfile)
		restore_stdout(shell);
	else
	{
		if (dup2(shell->out, STDOUT_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Dup2 shellout first builtin");
			exit(EXIT_FAILURE);
		}
	}
	if (cmds->last_infile)
		restore_stdin(shell, -1);
	else
	{
		if (dup2(shell->in, STDIN_FILENO) == -1)
		{
			ft_fprintf(STDERR_FILENO, "dup2 taking fd_in back %d\n", shell->in);
			exit(EXIT_FAILURE);
		}
	}
	return (fds[0]);
}
