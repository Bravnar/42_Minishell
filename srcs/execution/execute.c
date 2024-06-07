#include "minishell.h"



int	execute(t_cmds *cmds, t_main *shell)
{
	// char	*replaced;
	// char	*str;

	if (check_files(shell, cmds))
		return (EXIT_FAILURE);

	// str = ft_strdup("Hello $TERM , I am $PWD $SHLVL $HOMEBREW_CACHE $LS_COLORS");
	// replaced = var_replace(str, shell);
	// ft_printf("Attempt: %s\n", replaced);
	// free(replaced);
	// free(str);
	return (EXIT_SUCCESS);

}
