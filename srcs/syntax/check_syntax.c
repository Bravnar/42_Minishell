/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:18:25 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/07 14:31:10 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_quotes(t_lex *l)
{
	l->d_count = 0;
	l->d_quotes = 0;
	l->s_count = 0;
	l->s_quotes = 0;
	l->i = 0;
	
}

int	check_quotes(t_lex *l)
{
	l->i = -1;
	while (l->trim[++l->i])
	{
		if (l->trim[l->i] == '\'' && !l->d_quotes)
		{
			l->s_quotes = !l->s_quotes;
			l->s_count++;
		}
		else if (l->trim[l->i] == '\"' && !l->s_quotes)
		{
			l->d_quotes = !l->d_quotes;
			l->d_count++;
		}
	}
	if (l->s_count % 2 || l->d_count % 2)
		return (1);
	return (0);
}


/* void	check_syntax(t_lex *l)
{
	t_llex *current;
	t_llex *prev;

	current = l->link;
	prev = NULL;
	while (current)
	{
		if (current->value && ft_strchr(SPECIAL, current->value[0]))
			l->err_code = check_special(current->value);
		if (current->value && ft_strchr(QUOTES, current->value[0]))
			l->err_code = check_quotes(current->value);
	}
} */
