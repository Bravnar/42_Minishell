/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bravnar <bravnar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:55:15 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/04 18:57:49 by bravnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_main *shell)
{
	t_tok	*tok;
	t_lex	*lex;

	tok	= shell->tok;
	lex = shell->l;
	assign_types(tok, lex);
	assign_index(tok, lex);
}