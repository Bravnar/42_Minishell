/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:39:57 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/06 15:45:28 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lex(char *input)
{
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	p.work_line = ft_strtrim(input, WHITESPACE);
	p.args_list = ft_shellsplit(p.work_line, SPECIAL_W_SPACE);
	return (p.args_list);
}
