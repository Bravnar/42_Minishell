/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:51:12 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 10:51:15 by hmorand          ###   ########.ch       */
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

int	is_first(t_llex *l)
{
	if (!l->prev)
		return (1);
	return (0);
}

int	is_last(t_llex *l)
{
	if (!l->next)
		return (1);
	return (0);
}

int	set_err_code(char *value)
{
	if (!ft_strncmp(value, ">>", 2))
		return (BAD_REDIR_APP);
	else if (!ft_strncmp(value, "<<", 2))
		return (BAD_REDIR_HD);
	else if (!ft_strncmp(value, "<", 2))
		return (BAD_REDIR_IN);
	else if (!ft_strncmp(value, ">", 2))
		return (BAD_REDIR_OUT);
	else if (!ft_strncmp(value, "|", 2))
		return (BAD_PIPES);
	else if (!ft_strncmp(value, "\n", 2))
		return (BAD_REDIRS_NL);
	else
		return (999);
}
