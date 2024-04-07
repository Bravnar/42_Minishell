/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:39:57 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/07 12:21:57 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_validity(char **args, char *charset)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (args[++i])
	{
		if (ft_strchr(charset, args[i][0]))
		{
			j = -1;
			count = 0;
			while (args[i][++j] == args[i][0])
				count++;
			printf("Count in [%s]: %d\n", args[i], count);
			if (ft_strchr(REDIRS, args[i][0]) && count > 2)
				return (1);
			if (ft_strchr(PIPE, args[i][0]) && count > 1)
				return (1);
		}
	}
	return (0);
}

char	**lex(char *input)
{
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	p.work_line = ft_strtrim(input, WHITESPACE);
	p.args_list = ft_shellsplit(p.work_line, SPECIAL_W_SPACE);
	p.invalid_token = check_validity(p.args_list, SPECIAL);
	if (p.invalid_token)
		printf(RED"Token error detected\n"RESET);
	return (p.args_list);
}
