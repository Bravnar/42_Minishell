#include "minishell.h"

void	unset_node(t_envp **head, t_envp *iter, char *cmd)
{
	t_envp	*tmp;

	tmp = iter;
	if (!ft_strcmp(tmp->key, cmd))
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		else
			*head = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	unset_env(char **cmds, t_envp **head)
{
	t_envp	*tmp;
	t_envp	*next;
	int		i;

	i = 0;
	while (cmds[++i])
	{
		tmp = *head;
		while (tmp)
		{
			next = tmp->next;
			unset_node(head, tmp, cmds[i]);
			tmp = next;
		}
	}
	set_env(head, "?", "0", 777);
	return (EXIT_SUCCESS);
}
