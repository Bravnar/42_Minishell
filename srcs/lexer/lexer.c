/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:59:04 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/09 11:25:45 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_special(t_lex *l)
{
	char cur_special;
	
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
	(void) charset;
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
		else
			handle_other(l, charset);
	}
}

int	lexer(t_lex	*l)
{
	l->trim = ft_strtrim(l->input, WHITESPACE);
	reset_quotes(l);
	if (check_quotes(l))
		return (error_handler(BAD_QUOTES), 1);
	lex_input(l, SPECIAL_W_SPACE);
	/* if (check_redirs(&l->link))
		return (error_hadler(BAD_REDIRS), 1);
	if (check_pipes(&l->link))
		return (error_handler(BAD_PIPES), 1); */
	//check_simple_syntax(l);
	print_list(&l->link);
	return (0);
}

/* TO DO TODAY:
	--> Finish checking redirs and pipes
	--> Start working on type assigning logic
		--> Don't forget stuff like needs expansion Y/N
	--> Allocate an empty string


 */