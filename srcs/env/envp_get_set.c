#include "minishell.h"

/* Main getter function, searches through the t_envp
 linked list by key and returns the value */
char	*get_env(t_envp **head, char *var)
{
	t_envp	*tmp;
	char	*var_copy;

	var_copy = var;
	printf("in get_env: var is: %s\n", var_copy);
	tmp = *head;
	// if (*var == '\'')
	// 	return (handle_quote(head, var));
	if (*var_copy == '$')
		var_copy++;
	if (*var_copy == '~')
		return (handle_tilde(head, var_copy));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var_copy))
		{
			printf("am I here??\n");
			printf("key: %s value: %s\n",tmp->key, tmp->value);
			return (tmp->value);
		}
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
			printf("found env var %s\n", tmp->key);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			printf("set tmp.value of %s to : %s\n", tmp->key, tmp->value);
			printf("get_env result: %s\n", get_env(head, "?"));
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
