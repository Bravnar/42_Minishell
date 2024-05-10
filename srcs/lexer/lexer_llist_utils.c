/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_llist_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:22:18 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/10 19:18:46 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_llex	*new_token(char *value)
{
	t_llex	*token;

	token = malloc(sizeof(t_llex));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->is_in_quotes = 0;
	token->needs_exp = 0;
	token->index = 0;
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

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	print_list(t_llex **head)
{
	t_llex	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("(I:%d | V:%s | Q:%d | IS_ARG: %d | TYPE: %d)-->\n", \
			tmp->index, tmp->value, \
			tmp->is_in_quotes, tmp->needs_exp, tmp->type);
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
