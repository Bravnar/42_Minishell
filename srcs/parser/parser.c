/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:05:42 by smuravyev         #+#    #+#             */
/*   Updated: 2024/04/30 14:24:44 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_prelim(t_parse_prep **pre, t_token *tmp, int *i, int *j)
{
	
}

void	parser(t_token **t)
{
	t_parse_prep	*prelim;
	t_token			*tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	prelim = NULL;
	tmp = *t;
	populate_prelim(&prelim, tmp, &i, &j);
	create_cmd_table();
	
}