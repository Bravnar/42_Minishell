/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:55:15 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/09 11:39:01 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	work_list(t_tok *tok, t_llex *llex)
{
	t_llex	*tmp;

	tmp = llex;
	while (tmp)
	{
		llex->value
	}
}

void	parser(t_main *shell)
{
	t_tok	*tok;
	t_llex	*llex;

	tok	= shell->tok;
	llex = shell->l->link;
	work_list(tok, llex);
}