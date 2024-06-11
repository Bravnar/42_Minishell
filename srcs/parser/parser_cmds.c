#include "minishell.h"

int	count_commands(t_llex *head)
{
	t_llex	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp && tmp->type != PIPE_SYMBOL)
	{
		if (tmp->type == CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**duplicate_cmds(char **cmds)
{
	char	**result;
	int		i;

	i = -1;
	while (cmds[++i])
		;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		result[i] = ft_strdup(cmds[i]);
		//free(cmds[i]);
	}
	result[i] = NULL;
	//free(cmds);
	//cmds = NULL;
	return (result);
}

t_cmds	*new_cmds_node(char **cmds, t_files *files, int index, t_main *shell)
{
	t_cmds	*node;
	char	**paths;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	paths = get_paths(shell);
	if (!paths)
	{
		free(node);
		return (NULL);
	}
	node->path = get_path(paths, cmds[0]);
	ft_printf("Path: %s\n", node->path);
	ft_free_arr(paths);
	node->cmd_grp = duplicate_cmds(cmds);
	node->files = files;
	node->index = index;
	node->is_append = 0;
	node->is_heredoc = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_cmds_node(t_cmds **head, t_cmds *new_node)
{
	t_cmds	*tmp;

	if (!head)
		printf("Error: head is NULL\n");
	if (!new_node)
		printf("Error: new_node is NULL\n");
	if (!*head)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

char	*replace_expansion(t_llex *iter, t_main *shell)
{
	char	*work;
	int	i;

	i = 0;
	work = ft_strchr(iter->value, '$');
	printf("part where $ is: %s\n", work);
	printf("Entering replace expansion\n");
	printf("iter: %s\n", iter->value);
	(void) shell;
	exit (1);
}

char	*expand_if_needed(t_llex *iter, t_main *shell)
{
	char	*result;
	t_llex	*tmp;

	result = NULL;
	tmp = iter;
	if (tmp->is_in_quotes == 34)
		result = var_replace(tmp->value, shell);
	else if (!tmp->is_in_quotes)
		result = ft_strdup(get_env(&shell->env, tmp->value));
	else
		return (result);
	return (result);
}

// int	expand_if_needed(t_llex *iter, t_main *shell)
// {
// 	char	*expanded;

// 	if (iter->needs_exp)
// 	{
// 		if (iter->is_in_quotes == 34)
// 			iter->exp_tmp = var_replace(iter->value, shell);
// 		else if (!iter->is_in_quotes)
// 			iter->exp_tmp = get_env(&shell->env, iter->value);
// 		if (iter->exp_tmp && iter->exp_tmp != iter->value)
// 			return (1);
// 	}
// 	return (0);
// }

char	**create_cmd_arr(t_llex *tmp, t_main *shell, int count)
{
	char	**cmd_list;
	t_llex	*iter;
	int		i;

	(void) shell;
	iter = tmp;
	i = 0;
	cmd_list = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd_list)
		return (NULL);
	while (iter && iter->type != PIPE_SYMBOL)
	{
		if (iter && iter->type == CMD)
			cmd_list[i++] = ft_strdup(iter->value);
		iter = iter->next;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}

/* Create an ft_strreplace
  have the replace replace all occurences of items inside
  save that into the actual value, and then it will be freed by value? */