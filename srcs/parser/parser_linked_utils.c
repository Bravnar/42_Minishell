/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_linked_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:20:52 by smuravye          #+#    #+#             */
/*   Updated: 2024/05/10 15:54:01 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tok_new_token(char *value)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (!token)
		return (NULL);

	token->value = ft_strdup(value);
	token->is_in_quotes = 0;
	token->index = -1;
	token->needs_expansion = 0;
	token->type = NONE;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	tok_add_token(t_tok **token_list, t_tok *new_token)
{
	t_tok	*tmp;

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

void	tok_free_tokens(t_tok *token_list)
{
	t_tok	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	tok_print_list(t_tok **head)
{
	t_tok	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("(I:%d | V:%s | Q:%d | IS_ARG: %d | TYPE: %d)-->", \
			tmp->index, tmp->value, tmp->is_in_quotes, tmp->needs_expansion, tmp->type);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}

int	tok_ms_lstsize(t_tok *lst)
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
