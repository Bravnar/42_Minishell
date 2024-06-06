#include "minishell.h"

int	execute(t_cmds *cmds, t_main *shell)
{
	if (check_files(shell, cmds))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
