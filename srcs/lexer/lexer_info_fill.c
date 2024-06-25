/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_info_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:04:37 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 15:04:47 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tilde(t_llex *tmp)
{
	if (tmp->value[0] == '~' && !tmp->value[1])
	{
		if (!tmp->conn_with_prev && (!tmp->next || !tmp->next->conn_with_prev))
			tmp->needs_exp = 1;
	}
	else if (tmp->value[0] == '~' && tmp->value[1] == '/')
	{
		if (!tmp->conn_with_prev && (!tmp->next || !tmp->next->conn_with_prev))
			tmp->needs_exp = 2;
	}
}

void	overwrite_exp(t_llex *tmp)
{
	if (tmp->needs_exp)
	{
		if ((tmp->is_in_quotes && ft_strchr(CANCEL_EXP, tmp->value[2])) || \
		(ft_strchr(CANCEL_EXP, tmp->value[1])))
			tmp->needs_exp = 0;
	}
}

void	work_args(t_llex *tmp)
{
	char	*swap;

	swap = NULL;
	if (ft_strchr(QUOTES, tmp->value[0]))
		tmp->is_in_quotes = tmp->value[0];
	if (tmp->value[0] == '$')
		tmp->needs_exp = 1;
	else if (tmp->is_in_quotes == 34)
	{
		if (ft_strchr(tmp->value, '$'))
			tmp->needs_exp = 1;
	}
	overwrite_exp(tmp);
	check_tilde(tmp);
	swap = ft_strtrim(tmp->value, &tmp->is_in_quotes);
	free(tmp->value);
	tmp->value = swap;
}

void	fill_info(t_lex *l)
{
	t_llex	*tmp;
	int		index;

	tmp = l->link;
	index = 0;
	while (tmp)
	{
		work_args(tmp);
		tmp->index = index++;
		tmp = tmp->next;
	}
}
