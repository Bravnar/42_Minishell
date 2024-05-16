#include "minishell.h"

// void	free_cmds(t_cmds *token_list)
// {
// 	t_cmds	*tmp;

// 	if (!token_list)
// 		return ;
// 	while (token_list)
// 	{
// 		tmp = token_list;
// 		token_list = token_list->next;
// 		if (tmp->key)
// 			free(tmp->key);
// 		if (tmp->value)
// 			free(tmp->value);
// 		free(tmp);
// 	}
// }

t_cmds	*new_cmd_node(char *key, char *value)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	ft_bzero(node, 1);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_cmd_node(t_cmds **envp_head, t_cmds *new_envp_node)
{
	t_cmds	*tmp;

	if (!*envp_head)
	{
		*envp_head = new_envp_node;
	}
	else
	{
		tmp = *envp_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_envp_node;
		new_envp_node->prev = tmp;
	}
}

void	print_cmds(t_cmds **head)
{
	t_cmds	*tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		while (tmp->cmd_grp[++i])
			printf("%s\n");
		printf("File in: %s\n", tmp->file_in);
		printf("File out:%s\n", tmp->file_out);
	}
}
