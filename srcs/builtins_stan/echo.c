#include "minishell.h"

void	my_echo(t_main *shell, char **cmds)
{
	int	nl_needed;
	int	i;

	nl_needed = 1;
	i = 0;
	if (count_export_args(cmds) > 1)
	{
		if (!ft_strcmp(cmds[1], "-n"))
		{
			nl_needed = 0;
			i = 1;
		}
		while (cmds[++i])
		{
			if (i == (count_export_args(cmds) - 1))
				ft_fprintf(shell->out, "%s", cmds[i]);
			else
				ft_fprintf(shell->out, "%s ", cmds[i]);
		}
	}
	if (nl_needed)
		write(shell->out, "\n", 1);		
}
