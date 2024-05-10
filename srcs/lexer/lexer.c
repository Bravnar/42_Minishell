/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:59:04 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/10 17:19:04 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	work_args(t_llex *tmp)
{
	int		i;
	
	i = -1;
	if (ft_strchr(QUOTES, tmp->value[0]))
		tmp->is_in_quotes = tmp->value[0];
	if (tmp->value[0] == '$')
		tmp->needs_exp = 1;
	else if (tmp->is_in_quotes)
	{
		while (ft_strchr(QUOTES, tmp->value[++i]))
			;
		if (tmp->value[i - 1] == '\"' && tmp->value[i] == '$')
			tmp->needs_exp = 1;
	}
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

int	lexer(t_lex	*l)
{
	l->trim = ft_strtrim(l->input, WHITESPACE);
	reset_quotes(l);
	if (check_quotes(l))
		return (error_handler(l->err_code), 1);
	lex_input(l, SPECIAL_W_SPACE);
	if (check_redirs(l) || check_pipes(l))
		return (error_handler(l->err_code), 1);
	fill_info(l);
	print_list(&l->link);
	return (0);
}

/* int	check_redirs(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	while (tmp)
	{
		if (ft_strlen(tmp->value) > 2)
		{
			l->err_code = BAD_REDIRS;
			return (1);
		}
		if ((tmp->value[0] == '>' || tmp->value[0] == '<') \
			&& (tmp->value[1] == '\0' || tmp->value[1] == tmp->value[0]))
		{
			if (!tmp->next || !tmp->next->value)
			{
				l->err_code = BAD_REDIRS;
				return (1);
			}
			tmp = tmp->next;
		}
		l->err_code = BAD_REDIRS;
		return (1);
	}
	return (0);
} */

/* int	check_pipe(t_lex *l)
{
	t_llex *tmp;

	tmp = l->link;
	while (tmp)
	{
		if (ft_strlen(tmp->value) > 1)
		{
			l->err_code = BAD_PIPES;
			return (1);
		}
		if (tmp->value[0] == '|')
		{
			if (!tmp->next || !tmp->next->value)
			{
				l->err_code = BAD_PIPES;
				return (1);
			}
			tmp = tmp->next;
		}
		l->err_code = BAD_PIPES;
		return (1);
	}
	return (0);
} */



/* TO DO TODAY:
	--> Finish checking redirs and pipes
	--> Start working on type assigning logic
		--> Don't forget stuff like needs expansion Y/N
	--> Allocate an empty string


 */