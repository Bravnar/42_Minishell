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

t_cmds	*new_cmds_node(char **cmds, t_files *files, int index)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->cmd_grp = duplicate_cmds(cmds);
	node->files = files;
	node->index = index;
	node->file_in = NULL;
	node->file_out = NULL;
	node->is_append = 0;
	node->is_heredoc = 0;
	//get_last_infile(node, files);
	//get_last_outfile(node, files);
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
	//printf("What's in the head? %s\n", (*head)->file_in);
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

char	*expand_if_needed(t_llex *iter, t_main *shell)
{
	char	*expanded;

	if (iter->needs_exp)
	{
		expanded = ft_strdup(get_env(&shell->env, iter->value));
		if (expanded)
			return (expanded);
	}
	return (ft_strdup(iter->value));
}

char	**create_cmd_arr(t_llex *tmp, t_main *shell, int count)
{
	char	**cmd_list;
	t_llex	*iter;
	int		i;

	iter = tmp;
	i = 0;
	cmd_list = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd_list)
		return (NULL);
	while (iter && iter->type != PIPE_SYMBOL)
	{
		if (iter && iter->type == CMD)
			cmd_list[i++] = expand_if_needed(iter, shell);
		iter = iter->next;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
