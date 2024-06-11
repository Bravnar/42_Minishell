#include "minishell.h"

int	execute_cmd(t_cmds *cmds, int fds[2], int fd_in, t_main *shell)
{
	printf("fd_in %d\n", fd_in);
	close(fd_in);
	close(fds[0]);
	close(fds[1]);
	if (is_bad_command(cmds, shell))
		return (error_handler(shell->err_code,
				cmds->cmd_grp[0], shell), EXIT_FAILURE);
	execve(cmds->path, cmds->cmd_grp, shell->envp);
	perror("Execve");
	exit(EXIT_FAILURE);
}

int	piping(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	int		fds[2];
	pid_t	pid;

	if (!cmds->last_outfile)
		pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		if (cmds->last_infile)
			fd_in = redirect_input(cmds->last_infile);
		dup2(fd_in, shell->in);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile, shell);
		else
			dup2(fds[1], shell->out);
		execute_cmd(cmds, fds, fd_in, shell);
	}
	add_pid(pid, cpids);
	if (cmds->last_outfile)
	{
		close(fds[1]);
		return (fds[0]);
	}
	close(fds[0]);
	return (-1);
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
	tmp = cmds;
	fd_in = -1;
	while (tmp)
	{
		fd_in = piping(tmp, fd_in, cpids, shell);
		tmp = tmp->next;
	}
	wait_for_children(cpids);
	free(cpids);
	return (EXIT_SUCCESS);
}
