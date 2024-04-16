/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:45:32 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/11 18:57:14 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	count_args(char *str, char *charset)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] && (is_in_charset(str[i], charset) || str[i] == ' ') && !in_quotes)
			i++;
		if (str[i] && ft_strchr(QUOTES, str[i]))
		{
			if (!in_quotes)
				in_quotes = str[i];
			else if (in_quotes == str[i])
				in_quotes = 0;
			i++;
			continue ;
		}
		if (str[i])
		{
			count++;
			while (str[i] && !(is_in_charset(str[i], charset) || in_quotes))
			{
				if (str[i] == in_quotes)
				{
					in_quotes = 0;
					i++;
					break ;
				}
				i++;
			}
		}
	}
	return (count);
}
