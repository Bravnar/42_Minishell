#include "minishell.h"

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

