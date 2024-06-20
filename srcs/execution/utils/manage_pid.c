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

	status = 0;
	i = -1;
	if (cpids[0] == 0)
		return (0);
	while (cpids[++i])
	{
		// printf("Waiting for pid %d\n", cpids[i]);
		waitpid(cpids[i], &status, 0);
	}
	// printf("Out of wait\n");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

