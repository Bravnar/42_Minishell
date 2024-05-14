#include "minishell.h"

void	cd(char *dirname)
{
	if (chdir(dirname) != 0)
	{
		printf("cd: no such file or directory: %s", dirname);
		exit(2);
	}
}
