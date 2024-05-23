#include "minishell.h"

char	*my_get_path(void)
{
	char	*get_path;
	char	path[1024];

	get_path = NULL;
	get_path = getcwd(get_path, sizeof(path));
	return (get_path);
}

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
	free(get_path);
}

void	make_no_env_prompt(t_main *shell)
{
	char	*cwd;
	char	*first_part;
	char	*second_part;
	char	*final;

	if (shell->prompt)
		free(shell->prompt);
	cwd = my_get_path();
	first_part = ft_better_join(FACE, THROW);
	second_part = ft_better_join(first_part, cwd);
	final = ft_better_join(second_part, X_YELLOW);
	shell->prompt = ft_strdup(final);
	free(cwd);
	free(first_part);
	free(second_part);
	free(final);
}

void	no_env_handle(t_main *shell)
{
	shell->has_env = 0;
	shell->prompt = NULL;
	populate_no_env(shell);
	//make_no_env_prompt(shell);
}

char	*get_env(t_envp **head, char *var)
{
	t_envp	*tmp;

	tmp = *head;
	if (*var == '$')
		var++;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, var))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(t_envp **head, char *key, char *value)
{
	t_envp	*tmp;

	tmp = *head;
	if (*key == '$')
		key++;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
		}
		tmp = tmp->next;
	}
}

void	populate_envp(t_main *shell)
{
	int		i;
	int		tmp_num;
	char	**tmp_split;
	t_envp	*new_node;

	if (shell->envp[0] == NULL)
	{
		no_env_handle(shell);
		return ;
	}
	i = -1;
	while (shell->envp[++i])
	{
		tmp_split = ft_split(shell->envp[i], '=');
		if (!ft_strcmp(tmp_split[0], "SHLVL"))
		{
			tmp_num = ft_atoi(tmp_split[1]);
			tmp_num++;
			free(tmp_split[1]);
			tmp_split[1] = ft_itoa(tmp_num);
		}
		new_node = new_env_node(tmp_split[0], tmp_split[1]);
		add_env_node(&shell->env, new_node);
		ft_free_arr(tmp_split);
	}
}
