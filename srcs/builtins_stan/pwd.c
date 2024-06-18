#include "minishell.h"

void	my_pwd(t_main *shell)
{
	char	*pwd_to_print;

	pwd_to_print = my_get_path();
	ft_fprintf(shell->out, "%s\n", pwd_to_print);
	free(pwd_to_print);
}
