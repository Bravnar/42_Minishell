#include "minishell.h"

int	execute_cmd(t_cmds *cmds, t_main *shell)
{
	if (is_bad_command(cmds, shell))
		return (error_handler(shell->err_code,
				cmds->cmd_grp[0], shell), EXIT_FAILURE);
	if (!cmds->path)
		return (error_handler(NO_COMMAND, cmds->cmd_grp[0], shell), EXIT_FAILURE);
	execve(cmds->path, cmds->cmd_grp, shell->envp);
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
		if (cmds->last_infile)
			redirect_input(cmds->last_infile);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile);
		exit(execute_cmd(cmds, shell));
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
		if (cmds->last_infile)
			redirect_input(cmds->last_infile);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile);
		close_first_child(fds);
		exit(execute_cmd(cmds, shell));
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
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (cmds->last_infile)
			redirect_input(cmds->last_infile);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile);
		if (close(fd_in) == -1)
			exit(EXIT_FAILURE);
		exit(execute_cmd(cmds, shell));
	}
	add_pid(pid, cpids);
	if (close(fd_in) == -1)
		exit(EXIT_FAILURE);
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
		if (tmp->cmd_grp && tmp->cmd_grp[0])
		{
			if (!tmp->prev && !tmp->next)
				exec_single(tmp, cpids, shell);
			else if (!tmp->prev)
				fd_in = exec_pipeline_first(tmp, cpids, shell);
			else if (!tmp->next)
				fd_in = exec_pipeline_last(tmp, fd_in, cpids, shell);
			else
				fd_in = exec_pipeline_middle(tmp, fd_in, cpids, shell);
		}
		tmp = tmp->next;
	}
	wait_for_children(cpids);
	free(cpids);
	return (EXIT_SUCCESS);
}
