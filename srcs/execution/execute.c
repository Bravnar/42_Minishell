#include "minishell.h"

int	execute_cmd(t_cmds *cmds, t_main *shell)
{
	if (is_bad_command(cmds, shell))
		return (error_handler(shell->err_code,
				cmds->cmd_grp[0], shell), EXIT_FAILURE);
	execve(cmds->path, cmds->cmd_grp, shell->envp);
	perror("Execve");
	return(EXIT_FAILURE);
}

int piping(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	int fds[2];
	pid_t pid;

	printf("Before pipe - fd_in: %d\n", fd_in);
	if (cmds->next) // runs because there is a next command
	{
		if (pipe(fds) == -1) // creates a pipe
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0) // child process with ls -la
	{
		if (cmds->last_infile) // if infile
			fd_in = redirect_input(cmds->last_infile, shell);
		else if (fd_in != -1)
			redirect_stdin(fd_in, shell);
		if (cmds->last_outfile) //if it redirects output
			redirect_output(cmds->last_outfile, shell);
		else if (cmds->next)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			close(fds[0]);
		}
		exit(execute_cmd(cmds, shell));
	}
	else
	{
		add_pid(pid, cpids);
		if (!cmds->last_outfile)
		{
			printf("Here in parent - fd read: %d\n", fds[0]);
			if (fd_in != -1 && fd_in != STDIN_FILENO)
				close(fd_in);
			if (cmds->next || cmds->prev)
			{
				close(fds[1]);
				dup2(shell->in, fds[0]);
				close(fds[0]);
				return fds[0];
			}
		}
	}
	return(-1);
}

int	execute(t_cmds *cmds, t_main *shell)  // ls -la | wc -l
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
		if (tmp->cmd_grp[0])
			fd_in = piping(tmp, fd_in, cpids, shell);   // cmds (ls -la), -1, [0, ..., ...], shell
		printf("FD IN - loop: %d\n", fd_in);
		tmp = tmp->next;
	}
	wait_for_children(cpids);
	free(cpids);
	return (EXIT_SUCCESS);
}
