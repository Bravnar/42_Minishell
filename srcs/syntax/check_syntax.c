/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bravnar <bravnar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:18:25 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/04 15:05:54 by bravnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(t_lex	*l)
{
	l->err_code = NO_ERR;
}

void	check_redirs(t_lex	*l)
{
	l->err_code = NO_ERR;
}

void	check_pipes(t_lex	*l)
{
	l->err_code = NO_ERR;
}


void	check_syntax(t_lex *l)
{
	check_quotes(l);
	check_redirs(l);
	check_pipes(l);
	if (l->err_code)
		error_handler(l->err_code);
}