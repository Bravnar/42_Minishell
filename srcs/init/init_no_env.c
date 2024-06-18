#include "minishell.h"

t_envp	*new_no_env_node(char *key, char *value, int print)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = ft_strdup(key);
	if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->printable = print;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/* Function to populate the no environment linked list (hardcoded) */
void	populate_no_env(t_main *shell)
{
	t_envp	*new_node;
	char	*get_path;

	get_path = my_get_path();
	new_node = new_no_env_node("PWD", get_path, 1);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("SHLVL", "1", 1);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("_", "]", 1);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("HOME", NULL, 777);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("SECRET_HOME", NULL, 777);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("PATH", ENVLIN, 777);
	add_env_node(&shell->env, new_node);
	new_node = new_no_env_node("OLDPWD", NULL, 0);
	add_env_node(&shell->env, new_node);
	
	free(get_path);
}

void	make_no_env_prompt(t_main *shell)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;

	cwd = my_get_path();
	tmp = ft_better_join("sadshell:", cwd);
	tmp2 = ft_better_join(tmp, " $ ");
	free(cwd);
	shell->prompt = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
}

/* Main no_env function */
void	no_env_handle(t_main *shell)
{
	// char	*tmp;
	// char	*tmp2;
	// char	*cwd;

	// tmp = NULL;
	shell->has_env = 0;
	make_no_env_prompt(shell);
	// cwd = my_get_path();
	// tmp = ft_better_join("sadshell:", cwd);
	// tmp2 = ft_better_join(tmp, " $ ");
	// free(cwd);
	// shell->prompt = ft_strdup(tmp2);
	// free(tmp);
	// free(tmp2);
	populate_no_env(shell);
}