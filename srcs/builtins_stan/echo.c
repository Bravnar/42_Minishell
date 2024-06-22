#include "minishell.h"

int	my_echo(char **cmds, int fd)
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
				ft_fprintf(fd, "%s", cmds[i]);
			else
				ft_fprintf(fd, "%s ", cmds[i]);
		}
	}
	if (nl_needed)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);		
}
