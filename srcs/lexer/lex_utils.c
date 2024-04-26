/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:23:09 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/26 16:02:45 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input, t_quotes *q)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' && !q->in_double)
		{
			q->in_single = !q->in_single;
			q->count_s++;
		}
		else if (input[i] == '\"' && !q->in_single)
		{
			q->in_double = !q->in_double;
			q->count_d++;
		}
	}
	if (q->count_s % 2 || q->count_d % 2)
		return (1);
	return (0);
}

/* int	check_before(char *input, t_quotes *q)
{
	if (check_quotes(input, q))
		return (QUOTES_ERR);
	if (check_redirs(input, q))
		return (REDIR_ERR);
	if (check_pipes(input, q))
		return (PIPE_ERR);
} */

int	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	strlen_til_sep(char *str, char *charset)
{
	int	i;

	i = 0;
	if (is_in_charset(str[i], SPECIAL))
	{
		while (str[i] && str[i] == str[0])
			i++;
		return (i);
	}
	while (str[i] && !is_in_charset(str[i], charset))
		i++;
	return (i);
}
