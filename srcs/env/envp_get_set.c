#include "minishell.h"

/* Main getter function, searches through the t_envp
 linked list by key and returns the value */
char	*get_env(t_envp **head, char *var)
{
	t_envp	*tmp;

	tmp = *head;
	// if (*var == '\'')
	// 	return (handle_quote(head, var));
	if (*var == '$')
		var++;
	if (*var == '~')
		return (handle_tilde(head, var));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("\0");
}

/* Main setter function, searches through t_envp by key and changes the value */
void	set_env(t_envp **head, char *key, char *value, int print)
{
	t_envp	*tmp;
	t_envp	*new_node;

	new_node = NULL;
	tmp = *head;
	if (*key == '$')
		key++;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->printable = print;
			return ;
		}
		tmp = tmp->next;
	}
	new_node = new_env_node(key, value);
	add_env_node(head, new_node);
}

/* Main add function, adds a key : value + printable
 data to the end of t_envp */
void	add_env(t_main *shell, char *str)
{
	char	**split;

	split = NULL;
	if (ft_strchr(str, '='))
	{
		// split = ft_split(str, '=');
		split = export_split(str);
		if (!split[1])
			split[1] = ft_strdup("");
		set_env(&shell->env, split[0], split[1], 1);
	}
	else
		set_env(&shell->env, str, NULL, 0);
	ft_free_arr(split);
}
