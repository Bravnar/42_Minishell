#include "minishell.h"

void	free_nodes(t_envp *token_list)
{
	t_envp	*tmp;

	if (!token_list)
		return ;
	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value && tmp->value[0])
			free(tmp->value);
		free(tmp);
	}
}

t_envp	*new_env_node(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	if (!key)
		node->key = NULL;
	else
		node->key = ft_strdup(key);
	if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	if (!ft_strcmp(node->key, "HOME"))
		node->printable = 2;
	else if (!node->key || !node->value)
		node->printable = 0;
	else
		node->printable = 1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_env_node(t_envp **envp_head, t_envp *new_envp_node)
{
	t_envp	*tmp;

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

/* void	print_envp(t_envp **head)
{
	t_envp	*tmp;

	tmp = *head;

	//printf("{\n");
	set_env(head, "_", "/usr/bin/env");
	while (tmp != NULL)
	{
		// printf(BOLD_YELLOW"\t\"%s\" : \"%s\"\n"RESET, tmp->key, tmp->value);
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	// printf("}\n");
} */
