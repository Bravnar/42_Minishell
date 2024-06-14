#include "minishell.h"

void	add_pid(pid_t pid, pid_t *cpids)
{
	int		i;

	i = -1;
	while (cpids[++i])
		;
	cpids[i++] = pid;
	cpids[i] = 0;
}

int	wait_for_children(pid_t *cpids)
{
	int	status;
	int	i;

	i = -1;
	while (cpids[++i])
		waitpid(cpids[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

