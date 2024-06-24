#include "minishell.h"

void	set_underscore(t_cmds *cmds, t_main *shell)
{
	char	*underscore;
	int		i;

	if (cmd_size(cmds) > 1)
		return ;
	if (!cmds->cmd_grp)
	{
		underscore = ft_strdup("");
		set_env(&shell->env, "_", underscore, 777);
	}
	else
	{
		i = -1;
		while (cmds->cmd_grp[++i])
			;
		underscore = ft_strdup(cmds->cmd_grp[i - 1]);
		set_env(&shell->env, "_", underscore, 777);
	}
	free(underscore);
}
