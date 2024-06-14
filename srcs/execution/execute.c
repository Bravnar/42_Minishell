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

	if (!cmds->last_outfile) // runs because no outfile
	{
		if (pipe(fds) == -1) // creates a pipe
			exit(EXIT_FAILURE);
	}
	pid = fork(); 
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0) // child process with ls -la
	{
		if (cmds->last_infile) //skips
			fd_in = redirect_input(cmds->last_infile, shell);
		else if (fd_in != -1) //skips
		{
			dup2(fd_in, shell->in);
			close(fd_in);
		}
		else
			dup2(STDIN_FILENO, shell->in);
		if (cmds->last_outfile) //skips
			redirect_output(cmds->last_outfile, shell);
		else
		{
			dup2(fds[1], shell->out); 
			close(fds[1]);
		}
		close(fds[0]);
		exit(execute_cmd(cmds, shell));
	}
	else
	{
		add_pid(pid, cpids);
		close(fds[1]);
		if (!cmds->last_outfile)
		{
			dup2(fds[0], shell->in);
			//close(fds[0]);
			return fds[0];
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
		fd_in = piping(tmp, fd_in, cpids, shell);   // cmds (ls -la), -1, [0, ..., ...], shell
		tmp = tmp->next;
	}
	wait_for_children(cpids);
	free(cpids);
	return (EXIT_SUCCESS);
}
