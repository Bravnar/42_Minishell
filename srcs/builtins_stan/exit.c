#include "minishell.h"

int	my_exit(t_main *shell)
{
	free_all(shell);
	clear_t_cmds(shell);
	free_main(shell);
	exit(EXIT_SUCCESS);
}
