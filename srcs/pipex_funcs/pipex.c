#include "minishell.h"

void	child1(char **av, int *my_pipe, char **envp)
{
	int	fd;

	fd = my_open(av[1], 'i');
	dup2(fd, 0);
	dup2(my_pipe[1], 1);
	close(my_pipe[0]);
	exec(av[2], envp);
	exit(0);
}

void	child2(char **av, int *my_pipe, char **envp)
{
	int	fd;

	fd = my_open(av[4], 'o');
	dup2(fd, 1);
	dup2(my_pipe[0], 0);
	close(my_pipe[1]);
	exec(av[3], envp);
	exit(0);
}

void	parent(pid_t pid1, pid_t pid2, int *my_pipe)
{
	int	status;

	close(my_pipe[0]);
	close(my_pipe[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	exit(status);
}

int	main(int ac, char **av, char **envp)
{
	int		my_pipe[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!envp || !*envp)
		return (0);
	if (ac == 5)
	{
		if (pipe(my_pipe) == -1)
			exit(-1);
		pid1 = fork();
		if (pid1 < 0)
			exit(-1);
		if (!pid1)
			child1(av, my_pipe, envp);
		pid2 = fork();
		if (pid2 < 0)
			exit(-1);
		if (!pid2)
			child2(av, my_pipe, envp);
		parent(pid1, pid2, my_pipe);
		return (0);
	}
	ft_putendl_fd("pipex: invalid parameters", 2);
	exit(1);
}
