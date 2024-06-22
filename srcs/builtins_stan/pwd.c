#include "minishell.h"

int	my_pwd(int fd)
{
	char	*pwd_to_print;

	pwd_to_print = my_get_path();
	ft_fprintf(fd, "%s\n", pwd_to_print);
	free(pwd_to_print);
	return (EXIT_SUCCESS);
}
