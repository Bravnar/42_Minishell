#include "minishell.h"

void	env(char **ENV)
{
	int	i;

	i = -1;
	while (ENV[++i])
		printf("%s\n", ENV[i]);
}
/*
int	main(int argc, char *argv[], char *ENV[])
{
	(void) argv;
	(void) argc;

	env(ENV);
	return (-1);
} */
