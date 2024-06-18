#include "minishell.h"

t_envp	*new_no_env_node(char *key, char *value)
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
	if (!ft_strcmp(node->key, "HOME"))
		node->printable = 2;
	else if (!ft_strcmp(node->key, "COLUMNS"))
		node->printable = 2;
	else if (!node->key || !node->value)
		node->printable = 0;
	else
		node->printable = 1;
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
	new_node = new_env_node("PWD", get_path);
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("SHLVL", "1");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("_", "/usr/bin/env");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("HOME", NULL);
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