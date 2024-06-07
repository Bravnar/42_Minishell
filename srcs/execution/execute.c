#include "minishell.h"

int	redirect_output(t_files *outfile)
{
	int	fd;

	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf("dup2",);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	redirect_input(t_files *infile)
{
	int	fd;

	fd = open(infile->file_name, O_RDONLY);
	return (fd);
}

void	add_pid(pid_t pid, pid_t *cpids)
{
	while (*cpids)
		cpids++;
	*cpids++ = pid;
	*cpids = 0;
}

int	wait_for_children(pid_t *cpids)
{
	int	status;

	while (*cpids)
	{
		waitpid(*cpids, &status, 0);
		cpids++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	execute(t_pipex *pipex, int fds[2], int fd_in)
{
	close(fd_in);
	close(fds[0]);
	close(fds[1]);
	if (!pipex->commands[pipex->current].path)
	{
		ft_printf(STDERR_FILENO, "pipex: %s: command not found\n",
			pipex->commands[pipex->current].name);
		exit(127);
	}
	execve(pipex->commands[pipex->current].path,
		pipex->commands[pipex->current].args, pipex->env);
	perror("Execve");
	exit(EXIT_FAILURE);
}

int	piping(t_cmds *cmds, int fd_in)
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
		dup2(fd_in, STDIN_FILENO);
		if (cmds->last_outfile)
			redirect_output(cmds->last_outfile);
		else
			dup2(fds[1], STDOUT_FILENO);
		execute(pipex, fds, fd_in);
	}
	add_pid(pid, pipex->cpids);
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

	if (check_files(shell, cmds))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	tmp = cmds;
	fd_in = -1;
	while (tmp)
	{
		piping()
		tmp = tmp->next;
	}
}
