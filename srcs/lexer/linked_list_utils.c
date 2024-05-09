/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:22:18 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/09 16:11:50 by smuravye         ###   ########.fr       */
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
		printf("(%s)-->", tmp->value);
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
