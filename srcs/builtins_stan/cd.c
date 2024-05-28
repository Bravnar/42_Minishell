#include "minishell.h"

void	go_home(t_main *shell, char **cmds, char *old_pwd)
{
	char	*home_dir;
	// char	*tmp;

	(void) cmds;
	(void) old_pwd;
	//if (!cmds[1] && !shell->has_env)
	home_dir = get_env(&shell->env, "HOME");
	printf("im in go_home, the home_dir is -> %s\n", home_dir);
	// tmp = get_env(&shell->env, "HOME");
	// home_dir = ft_strtrim(tmp, "/");
	//printf("home_dir: %s\n", home_dir);
	// free(tmp);
	if (chdir(home_dir) == -1)
		printf(BOLD_RED"chdir error\n"RESET);
	//free(home_dir);
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
void	swap_old_new(t_main *shell, char **cmds, char *old_pwd)
{
	(void) cmds;
	old_pwd = get_env(&shell->env, "OLDPWD");
	if (chdir(old_pwd) == -1)
		printf(BOLD_RED"chdir error\n"RESET);
	//free(old_pwd);
}
void	cd_go(t_main *shell, char **cmds, char *old_pwd)
{
	(void) shell;
	(void) old_pwd;
	if (chdir(cmds[1]) == -1)
		printf(BOLD_RED"TMP! minishell: cd: %s: No such file or directory\n"RESET, cmds[1]);
}

void	cd_go_back(t_main *shell, char **cmds, char *old_pwd)
{
	(void) shell;
	(void) old_pwd;
	if (!ft_strcmp(cmds[1], ".."))
	{
		if (chdir(cmds[1]) == -1)
			printf(BOLD_RED"chdir error\n"RESET);
	}
	else if (chdir(cmds[1]))
		printf(BOLD_RED"chdir error\n"RESET);

}

int	cd_count(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	if (i > 2)
		return (1);
	return (0);
}

void	cd(t_main *shell, char **cmds)
{
	char	*old_pwd;

	old_pwd = get_env(&shell->env, "PWD");
	if (cd_count(cmds))
	{
		ft_fprintf(2, BOLD_RED"TMP! %s %s: %s\n"RESET, MSHELL, cmds[0], TOO_MANY_ARGS);
		return ;
	}
	//if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
	if (!cmds[1])
		go_home(shell, cmds, old_pwd);
	else if (cmds[1][0] == '-')
	{
		old_pwd = get_env(&shell->env, "PWD");
		swap_old_new(shell, cmds, old_pwd);
	}
	else if (cmds[1] != NULL \
		&& ft_strcmp(cmds[1], "..") && cmds[1][0] != '-')
		cd_go(shell, cmds, old_pwd);
	else if (!ft_strcmp(cmds[1], "..") || !ft_strncmp(cmds[1], "../", 3))
		cd_go_back(shell, cmds, old_pwd);
	adjust_pwd(shell, old_pwd);
	//printf(BOLD_YELLOW"PWD: %s\n"RESET, get_env(&shell->env, "PWD"));
	//printf(BOLD_YELLOW"OLDPWD: %s\n"RESET, get_env(&shell->env, "OLDPWD"));
}

/* void	cd_check(t_main *shell, char **cmds, char *old_pwd)
{
	if (!cmds[1] || cmds[1][0] == '~')
		cd_home(shell);
	else if (cmds[1][0] == '-')
		cd_swap(shell, old_pwd);
	
}

void	cd_main(t_main *shell, char **cmds)
{
	char	*old_pwd;

	old_pwd = get_env(&shell->env, "PWD");
	if (cd_count(cmds))
	{
		shell->err_code = MANY_ARGS;
		return (error_handler(shell->err_code));
	}
	if (!cmds || !cmds[0])
		return ;
	cd_check(shell, cmds, old_pwd);
	adjust_pwd(shell, old_pwd);
} */




/* TODAY:
	Finish cd and test everything
	Organise all the files, for the builtins
	Finish env + (env utils)
	Start export (x=y etc.)
	Create unset
 */