#include "minishell.h"

void	free_local_copy(t_envp *local)
{
	t_envp	*tmp;

	if (!local)
		return ;
	while (local)
	{
		tmp = local;
		local = local->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	tmp = NULL;
}
int	count_export_args(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

void	print_local_copy(t_envp **head, int fd)
{
	t_envp	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->printable != 777)
		{
			if (!(tmp->key && tmp->key[0] == '_' && !tmp->key[1]))
			{
				if (!tmp->value)
					ft_fprintf(fd ,"declare -x %s\n", tmp->key);
				else
					ft_fprintf(fd, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			}
		}
		tmp = tmp->next;
	}
}

void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr)
{
	n_n->key = ft_strdup(curr->key);
	n_n->value = ft_strdup(curr->value);
	n_n->printable = curr->printable;
	n_n->next = NULL;
	n_n->prev = *l_t;
	if (*l_t)
		(*l_t)->next = n_n;
	else
		*l_h = n_n;
	*l_t = n_n;
}

t_envp	*copy_list(t_envp *src)
{
	t_envp	*local_head;
	t_envp	*local_tail;
	t_envp	*current;
	t_envp	*new_node;

	local_head = NULL;
	local_tail = NULL;
	current = src;
	while (current)
	{
		new_node = malloc(sizeof(t_envp));
		if (!new_node)
		{
			free_local_copy(local_head);
			return (NULL);
		}
		copy_work(new_node, &local_head, &local_tail, current);
		current = current->next;
	}
	return (local_head);
}

void	swap_nodes(t_envp *a, t_envp *b)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_printable;

	tmp_key = a->key;
	tmp_value = a->value;
	tmp_printable = a->printable;
	a->key = b->key;
	a->value = b->value;
	a->printable = b->printable;
	b->key = tmp_key;
	b->value = tmp_value;
	b->printable = tmp_printable;
}


void	sort_local_copy(t_envp	**local)
{
	int		swapped;
	t_envp	*tmp;

	if (!local || !*local)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = *local;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_nodes(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}

char	**export_split(char *str)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = malloc((sizeof(char *) * 3));
	if (!result)
		return (NULL);
	while (str[j] != '=')
		j++;
	result[0] = ft_substr(str, i, j - i);
	i = ++j;
	while (str[j])
		j++;
	result[1] = ft_substr(str, i, j - i);
	result[2] = NULL;
	return (result);

}

int	export(t_main *shell, char **cmds, int fd)
{
	t_envp	*local;
	int		count;
	int		i;

	i = 1;
	count = count_export_args(cmds);
	if (count > 1)
	{
		while (cmds[i])
		{
			if (cmds[i][0] == '=')
				error_handler(EXPORT_ERR, cmds[i++], shell);
			else
				add_env(shell, cmds[i++]);
		}
		set_env(&shell->env, "_", cmds[count - 1], 1);
		return (EXIT_SUCCESS);

	}
	local = copy_list(shell->env);
	if (!local)
		return (EXIT_SUCCESS);
	sort_local_copy(&local);
	print_local_copy(&local, fd);
	free_local_copy(local);
	set_env(&shell->env, "_", cmds[count - 1], 1);
  return(EXIT_SUCCESS);
}
