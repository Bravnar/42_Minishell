/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:59:04 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/10 19:20:24 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(t_lex *l)
{
	l->j++;
	if (l->trim[l->j] == '$')
	{
		l->j++;
		add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));
	}
	else
	{
		while (l->trim[l->j] && !ft_strchr(SPECIAL_W_SPACE, l->trim[l->j]))
			l->j++;
		add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));
	}
	l->i = l->j;
}

void	handle_special(t_lex *l)
{
	char	cur_special;

	cur_special = l->trim[l->j];
	while (l->trim[l->j] == cur_special)
		l->j++;
	add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));
	l->i = l->j;
}

void	handle_other(t_lex *l, char *charset)
{
	while (l->trim[l->j] && !ft_strchr(charset, l->trim[l->j]))
		l->j++;
	add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));
	l->i = l->j;
}

void	handle_quotes(t_lex *l)
{
	l->j++;
	while (l->trim[l->j] && l->trim[l->j] != l->q_char)
		l->j++;
	if (l->trim[l->j] == l->q_char)
		l->j++;
	add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));
	l->i = l->j;
	l->q_char = 0;
}

void	lex_input(t_lex *l, char *charset)
{
	if (!l->trim)
		return ;
	l->i = 0;
	l->j = 0;
	while (l->trim[l->j])
	{
		while (l->trim[l->j] && ft_strchr(WHITESPACE, l->trim[l->j]))
			l->j++;
		l->i = l->j;
		if (!l->q_char && ft_strchr(QUOTES, l->trim[l->j]))
		{
			l->q_char = l->trim[l->j];
			handle_quotes(l);
		}
		else if (l->trim[l->j] && ft_strchr(SPECIAL, l->trim[l->j]))
			handle_special(l);
		else if (l->trim[l->j] == '$' && !l->q_char)
			handle_dollar(l);
		else
			handle_other(l, charset);
	}
}

