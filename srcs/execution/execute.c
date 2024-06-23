#include "minishell.h"

int	execute_cmd(t_cmds *cmds, t_main *shell)
{
	if (!cmds->cmd_grp)
	{
		if (cmds->last_infile || cmds->last_outfile)
			{
				ft_fprintf(STDERR_FILENO, "Exiting cause no command\n");
				return(EXIT_SUCCESS);
			}

	}
	if (is_bad_command(cmds, shell))
		return (error_handler(shell->err_code,
				cmds->cmd_grp[0], shell), EXIT_FAILURE);
	if (!cmds->path)
		return (error_handler(NO_COMMAND, cmds->cmd_grp[0], shell), EXIT_FAILURE);
	shell->envp = back_to_array(shell->env); // stan line
	execve(cmds->path, cmds->cmd_grp, shell->envp);
	ft_free_arr(shell->envp); // stan line
	perror("Execve");
	return(EXIT_FAILURE);
}

int exec_single(t_cmds *cmds, pid_t *cpids, t_main *shell)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		handle_redirection(cmds);
		return(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	return(-1);
}

int exec_pipeline_first(t_cmds *cmds, pid_t *cpids, t_main *shell)
{
	int fds[2];
	pid_t pid;

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		handle_redirection(cmds);
		close_first_child(fds);
		return(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	close_first_parent(fds);
	return (fds[0]);
}

int exec_pipeline_last(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (!cmds->last_infile)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		handle_redirection(cmds);
		close_fdin_last_child(fd_in);
		return(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	close_fdin_last_parent(fd_in);
	return (-1);
}

int exec_pipeline_middle(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	int fds[2];
	pid_t pid;

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
		handle_redirection(cmds);
		close_middle_child(fds, fd_in);
		return(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	close_middle_parent(fds, fd_in);
	return (fds[0]);
}

void	piping(t_cmds *tmp, pid_t *cpids, int *fd_in, t_main *shell)
{
	if (tmp->cmd_grp && tmp->cmd_grp[0])
	{
		if (!tmp->prev && !tmp->next)
		{
			if (!tmp->is_builtin)
				exec_single(tmp, cpids, shell);
			else
				exec_single_builtin(tmp, shell);
		}
		else if (!tmp->prev)
		{
			if (!tmp->is_builtin)
				*fd_in = exec_pipeline_first(tmp, cpids, shell);
			else
				*fd_in = exec_first_builtin(tmp, shell);
		}
		else if (!tmp->next)
		{
			if (!tmp->is_builtin)
				*fd_in = exec_pipeline_last(tmp, *fd_in, cpids, shell);
			else
				*fd_in = exec_last_builtin(tmp, *fd_in, shell);
		}
		else
			*fd_in = exec_pipeline_middle(tmp, *fd_in, cpids, shell);
	}
}

int	execute(t_cmds *cmds, t_main *shell)
{
	t_cmds	*tmp;
	int		fd_in;
	pid_t	*cpids;
	
	if (check_files(shell, cmds))
		return (EXIT_FAILURE);
	cpids = malloc(sizeof(pid_t) * (cmd_size(cmds) + 1));
	if (!cpids)
		return (EXIT_FAILURE);
	cpids[0] = 0;
	tmp = cmds;
	fd_in = -1;
	while (tmp)
	{
		piping(tmp, cpids, &fd_in, shell);
		tmp = tmp->next;
	}
	wait_for_children(cpids);
	free(cpids);
	return (EXIT_SUCCESS);
}
