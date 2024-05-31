#include "minishell.h"

void	go_home(t_main *shell, char **cmds, char *cwd)
{
	char	*home_dir;

	home_dir = get_env(&shell->env, "HOME");
	if (!ft_strcmp(cwd, home_dir))
		return ;
	if (!home_dir)
	{
		ft_fprintf(2, BOLD_RED"%s %s: %s\n"RESET, MSHELL, cmds[0], NO_HOME);
		return ;
	}
	if (chdir(home_dir) == -1)
		ft_fprintf(2, BOLD_RED"chdir error\n"RESET);
}

void	swap_old_new(t_main *shell, char **cmds, char *old_pwd)
{
	(void) cmds;
	old_pwd = get_env(&shell->env, "OLDPWD");
	if (chdir(old_pwd) == -1)
		printf(BOLD_RED"chdir error\n"RESET);
	//free(old_pwd);
}

void	adjust_pwd(t_main *shell, char *old_pwd)
{
	char	path[1024];
	char	*get_path;

	get_path = NULL;
	get_path = getcwd(get_path, sizeof(path));
	set_env(&shell->env, "OLDPWD", old_pwd);
	set_env(&shell->env, "PWD", get_path);
	free(get_path);
}

int	cd_count(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

void	cd_new(t_main *shell, char **cmds)
{
	char	*old_pwd;

	old_pwd = get_env(&shell->env, "PWD");
	if (cd_count(cmds) > 2)
	{
		ft_fprintf(2, BOLD_RED"%s %s: %s\n"RESET, \
			MSHELL, cmds[0], TOO_MANY_ARGS);
		return ;
	}
	if (cd_count(cmds) == 1 || cmds[1][0] == '~')
		go_home(shell, cmds, old_pwd);
	else if (cd_count(cmds) == 2 && !ft_strcmp(cmds[1], "-"))
		swap_old_new(shell, cmds, old_pwd);
	else
	{
		if (chdir(cmds[1]) == -1)
			ft_fprintf(2, BOLD_RED"chdir error\n"RESET);
	}
	adjust_pwd(shell, old_pwd);
}
/*
TO DO with CD
1) Create a separate function that will handle no env
2) Fix prompt generation when outside of constraints of '~'

*/