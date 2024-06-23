#include "minishell.h"

int	builtins(t_cmds *cmds, t_main *shell, int fd)
{
	if (cmds && cmds->cmd_grp && cmds->cmd_grp[0])
	{
		if (!ft_strcmp(cmds->cmd_grp[0], "cd"))
			return(cd_new(shell, cmds->cmd_grp));
		else if (!ft_strcmp(cmds->cmd_grp[0], "env"))
			return(print_envp(&shell->env, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "export"))
			return(export(shell, cmds->cmd_grp, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "echo"))
			return(my_echo(cmds->cmd_grp, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "unset"))
			return(unset_env(cmds->cmd_grp, &shell->env));
		else if (!ft_strcmp(cmds->cmd_grp[0], "pwd"))
			return(my_pwd(fd, shell, cmds->cmd_grp));
		else if (!ft_strcmp(cmds->cmd_grp[0], "exit"))
			return(my_exit(shell, cmds->cmd_grp));
	}
	return (EXIT_FAILURE);
}

int exec_single_builtin(t_cmds *cmds, t_main *shell)
{
	t_stds	fd_stds;

	fd_stds.in = -1;
	fd_stds.out = -1;
	if (cmds->last_infile)
		fd_stds.in = redirect_input_builtin(cmds->last_infile, shell);
	if (cmds->last_outfile)
		redirect_output_builtin(cmds->last_outfile, shell);
	shell->err_code = builtins(cmds, shell, STDOUT_FILENO);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (cmds->last_infile)
		restore_stdin(shell, fd_stds.in);
	return (shell->err_code);
}

int exec_first_builtin(t_cmds *cmds, t_main *shell)
{
	int	fds[2];
	t_stds	fd_stds;

	save_stdout(shell);
	fd_stds.in = -1;
	fd_stds.out = -1;
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	redir_builtin(cmds, shell, &fd_stds, FIRST);
	builtins(cmds, shell, STDOUT_FILENO);
	close_first_parent(fds);
	if (cmds->last_infile)
		restore_stdin(shell, fd_stds.in);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (dup2(shell->out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	return (fds[0]);
}

int	exec_last_builtin(t_cmds *cmds, int fd_in, t_main *shell)
{
	t_stds	fd_stds;

	save_stdin(shell);
	if (cmds->last_infile)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	redir_builtin(cmds, shell, &fd_stds, LAST);
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

/* int exec_pipeline_middle(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	int fds[2];
	pid_t pid;

	save_stdin(shell);
	s
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (cmds->last_infile)
			redirect_input(cmds->last_infile);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile);
		close_middle_child(fds, fd_in);
		exit(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	close_middle_parent(fds, fd_in);
	return (fds[0]);
} */
