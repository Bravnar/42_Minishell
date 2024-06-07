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

void	print_local_copy(t_envp **head)
{
	t_envp	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (!(tmp->key && tmp->key[0] == '_' && !tmp->key[1]))
		{
			if (!tmp->value)
				printf("declare -x %s\n", tmp->key);
			else
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}

void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr)
{
	n_n->key = ft_strdup(curr->key);
	n_n->value = ft_strdup(curr->value);
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

void	export(t_main *shell, char **cmds)
{
	t_envp	*local;
	int		count;
	int		i;

	i = 1;
	count = count_export_args(cmds);
	if (count > 1)
	{
		while (cmds[i])
			add_env(shell, cmds[i++]);
		set_env(&shell->env, "_", cmds[count], 1);
		return ;
	}
	local = copy_list(shell->env);
	if (!local)
		return ;
	sort_local_copy(&local);
	print_local_copy(&local);
	free_local_copy(local);
	set_env(&shell->env, "_", cmds[count], 1);
}
