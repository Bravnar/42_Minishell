#include "minishell.h"

int	is_valid_n(const char *arg)
{
	int	i;

	i = 2;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	my_echo(char **cmds, int fd)
{
	int	nl_needed;
	int	i;

	nl_needed = 1;
	i = 1;
	while (cmds[i] && is_valid_n(cmds[i]))
	{
		nl_needed = 0;
		i++;
	}
	// if (count_export_args(cmds) > 1)
	// {
	// 	if (!ft_strcmp(cmds[1], "-n"))
	// 	{
	// 		nl_needed = 0;
	// 		i = 1;
	// 	}
		// while (cmds[++i])
		// {
		// 	if (i == (count_export_args(cmds) - 1))
		// 		ft_fprintf(fd, "%s", cmds[i]);
		// 	else
		// 		ft_fprintf(fd, "%s ", cmds[i]);
		// }
	while (cmds[i])
	{
		ft_fprintf(fd, "%s", cmds[i]);
		if (cmds[i + 1])
			ft_fprintf(fd, " ");
		i++;
	}
	if (nl_needed)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}
