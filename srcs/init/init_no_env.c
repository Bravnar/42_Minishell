#include "minishell.h"

/* Function to populate the no environment linked list (hardcoded) */
void	populate_no_env(t_main *shell)
{
	t_envp	*new_node;
	char	*get_path;

	get_path = my_get_path();
	new_node = new_env_node("PWD", get_path);
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("SHLVL", "1");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("_", "/usr/bin/env");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("HOME", NULL);
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("COLUMNS", "1000");
	free(get_path);
}

/* Main no_env function */
void	no_env_handle(t_main *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*cwd;

	tmp = NULL;
	shell->has_env = 0;
	cwd = my_get_path();
	tmp = ft_better_join("sadshell:", cwd);
	tmp2 = ft_better_join(tmp, " $ ");
	free(cwd);
	shell->prompt = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
	populate_no_env(shell);
}