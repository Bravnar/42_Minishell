#include "minishell.h"

void	add_pid(pid_t pid, pid_t *cpids)
{
	int				i;

	i = -1;
	while (cpids[++i])
		;
	cpids[i++] = pid;
	pid_for_signal(&pid);
	cpids[i] = 0;
}

int	wait_for_children(pid_t *cpids, t_main *shell)
{
	int	status;
	int	i;
	char	*convert_status;

	status = 0;
	i = -1;
	if (cpids[0] == 0)
		return (0);
	while (cpids[++i])
	{
		// printf("Waiting for pid %d\n", cpids[i]);
		waitpid(cpids[i], &status, 0);
	}
	convert_status = ft_itoa(status % 255);
	set_env(&shell->env, "?", convert_status, 777);
	free(convert_status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

