#include "minishell.h"

t_llex	*new_token(char *value,	int is_con)
{
	t_llex	*token;

	//token = malloc(sizeof(t_llex));
	token = ft_calloc(1, sizeof(t_llex));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->is_in_quotes = 0;
	token->needs_exp = 0;
	token->index = 0;
	if (is_con)
		token->conn_with_prev = 1;
	else
		token->conn_with_prev = 0;
	token->exp_tmp = NULL;
	token->type = NONE;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_llex **token_list, t_llex *new_token)
{
	t_llex	*tmp;

	if (!*token_list)
	{
		*token_list = new_token;
	}
	else
	{
		tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

void	free_tokens(t_llex *token_list)
{
	t_llex	*tmp;

	if (!token_list)
		return ;
	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		// printf("freeing tmp->value: %s\n", tmp->value); removed 07/06 to test leaks and double free!, uncomment all to revert
		free(tmp->value);
		// printf("value of tmp->exp_tmp: %s\n", tmp->exp_tmp);
		// if (tmp->exp_tmp && tmp->exp_tmp[0])
		// {
		// 	printf("im here\n");
		// 	free(tmp->exp_tmp);
		// 	tmp->exp_tmp = NULL;
		// }
		free(tmp);
	}
	tmp = NULL;
}

void	print_list(t_llex **head)
{
	t_llex	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("(I:%d | V:%s | Q:%d | IS_VAR: %d | IS_CON: %d | TYPE: %d)-->\n", \
			tmp->index, tmp->value, \
			tmp->is_in_quotes, tmp->needs_exp, tmp->conn_with_prev, tmp->type);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}

int	ms_lstsize(t_llex *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
