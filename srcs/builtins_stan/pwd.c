#include "minishell.h"


int	my_pwd(int fd, t_main *shell, char **cmds)
{
	char	*pwd_to_print;
	int		cmds_count;

	cmds_count = count_export_args(cmds);
	pwd_to_print = my_get_path();
	ft_fprintf(fd, "%s\n", pwd_to_print);
	free(pwd_to_print);
	set_env(&shell->env, "_", cmds[cmds_count - 1], 1);
	return (EXIT_SUCCESS);
}
