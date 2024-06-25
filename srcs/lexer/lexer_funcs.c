/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:05:44 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 15:05:50 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(t_lex *l)
{
	char	*substr;
	int		is_con;

	is_con = 0;
	if (l->j > 0 && !(ft_strchr(WHITESPACE, l->trim[l->j - 1])))
		is_con = 1;
	l->j++;
	if (ft_strchr(DOLLAR_CHARS, l->trim[l->j]))
	{
		l->j++;
		substr = ft_substr(l->trim, l->i, l->j - l->i);
		add_token(&l->link, new_token(substr, is_con));
		free(substr);
	}
	else
	{
		while (l->trim[l->j] && !ft_strchr(SPECIAL_W_SPACE, l->trim[l->j]) && \
			(ft_isalnum(l->trim[l->j]) || l->trim[l->j] == '_'))
			l->j++;
		substr = ft_substr(l->trim, l->i, l->j - l->i);
		add_token(&l->link, new_token(substr, is_con));
		free(substr);
	}
	l->i = l->j;
}

void	handle_special(t_lex *l)
{
	char	cur_special;
	char	*substr;
	int		is_con;

	is_con = 0;
	if (l->j > 0 && !(ft_strchr(WHITESPACE, l->trim[l->j - 1])))
		is_con = 1;
	cur_special = l->trim[l->j];
	while (l->trim[l->j] == cur_special)
		l->j++;
	substr = ft_substr(l->trim, l->i, l->j - l->i);
	add_token(&l->link, new_token(substr, is_con));
	free(substr);
	l->i = l->j;
}

void	handle_other(t_lex *l, char *charset)
{
	char	*substr;
	int		is_con;

	is_con = 0;
	if (l->j > 0 && !(ft_strchr(WHITESPACE, l->trim[l->j - 1])))
		is_con = 1;
	while (l->trim[l->j] && !ft_strchr(charset, l->trim[l->j]))
		l->j++;
	substr = ft_substr(l->trim, l->i, l->j - l->i);
	add_token(&l->link, new_token(substr, is_con));
	free(substr);
	l->i = l->j;
}

void	handle_quotes(t_lex *l)
{
	char	*substr;
	int		is_con;

	is_con = 0;
	if (l->j > 0 && !(ft_strchr(WHITESPACE, l->trim[l->j - 1])))
		is_con = 1;
	l->j++;
	while (l->trim[l->j] && l->trim[l->j] != l->q_char)
		l->j++;
	if (l->trim[l->j] == l->q_char)
		l->j++;
	substr = ft_substr(l->trim, l->i, l->j - l->i);
	add_token(&l->link, new_token(substr, is_con));
	free(substr);
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

//add_token(&l->link, new_token(ft_substr(l->trim, l->i, l->j - l->i)));