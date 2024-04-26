/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:12:46 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/26 16:16:49 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);

	token->value = ft_strdup(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*tmp;

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

void	free_tokens(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	print_list(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("(%s, SP_BEFORE: %d, SP_AFTER: %d)-->", tmp->value, tmp->has_space_before, tmp->has_space_after);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}
