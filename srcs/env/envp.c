#include "minishell.h"

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

void	populate_envp(t_main *shell)
{
	int		i;
	int		tmp_num;
	char	**tmp_split;
	t_envp	*new_node;

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
