#include "minishell.h"

void	pwd(void)
{
	printf("%s", getcwd(NULL, 0));
}
