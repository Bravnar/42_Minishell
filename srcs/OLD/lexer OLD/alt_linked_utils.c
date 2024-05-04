#include "minishell.h"

t_lex	*new_token(char *value)
{
	t_lex	*token;

	token = malloc(sizeof(t_lex));
	if (!token)
		return (NULL);

	token->value = ft_strdup(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_lex **token_list, t_lex *new_token)
{
	t_lex	*tmp;

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

void	free_tokens(t_lex *token_list)
{
	t_lex	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	print_list(t_lex **head)
{
	t_lex	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		// printf("(%s, SP_BEFORE: %d, SP_AFTER: %d)-->", tmp->value, tmp->has_space_before, tmp->has_space_after);
		printf("(%s)-->", tmp->value);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}