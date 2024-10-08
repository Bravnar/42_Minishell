/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:06:38 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 15:06:38 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* The lexer works on the basis of the piscine ft_split
   With 2 key differences, it keeps the separator chars
   and it creates a linked list instead of a char **
   1) Trims the user input
   2) (Resets the quote storage variables in case of an nth call)
   3) Checks if the quotes are correct BEFORE tokenizing
   4) Goes through the ft_split motion and creates
      a linked list with all elements
   5) checks correct redirs and correct pipes
   6) fill_info() goes over the linked list and
      fills the info such as expansion, space and quotes
   7) Calls the parser function (move to main) */

int	lexer(t_lex	*l, t_main *shell)
{
	l->trim = ft_strtrim(l->input, WHITESPACE);
	reset_quotes(l);
	if (check_quotes(l))
		return (error_handler(l->err_code, NULL, shell), 1);
	lex_input(l, SPECIAL_W_SPACE);
	fill_info(l);
	if (check_redirs(l) || check_pipes(l) || check_spec(l))
		return (error_handler(l->err_code, NULL, shell), 1);
	parser_main(shell);
	return (0);
}
