#include "minishell.h"

int	is_builtin(t_cmds *cmds)
{
	if (cmds->cmd_grp)
	{
		if (!ft_strcmp(cmds->cmd_grp[0], "echo") || \
			!ft_strcmp(cmds->cmd_grp[0], "cd") || \
			!ft_strcmp(cmds->cmd_grp[0], "env") || \
			!ft_strcmp(cmds->cmd_grp[0], "export") || \
			!ft_strcmp(cmds->cmd_grp[0], "pwd") || \
			!ft_strcmp(cmds->cmd_grp[0], "unset") || \
			!ft_strcmp(cmds->cmd_grp[0], "exit"))
		{
			cmds->is_builtin = 1;
			return (1);
		}
	}
	cmds->is_builtin = 0;
	return (0);
}


void	check_builtins(t_cmds *cmds)
{
	t_cmds	*temp;

	temp = cmds;
	while (temp)
	{
		is_builtin(temp);
		temp = temp->next;
	}
}