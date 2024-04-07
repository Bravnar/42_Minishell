/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shellsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:39:40 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/07 11:38:07 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_charset(char c, char *charset)
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

static int	count_strs(char *str, char *charset)
{
	int	i;
	int	elem_count;

	i = 0;
	elem_count = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] && is_in_charset(str[i], charset))
		{
			if (!(str[i + 1] == str[i] || str[i] == ' '))
				elem_count++;
			i++;
		}
		if (str[i])
			elem_count++;
		while (str[i] && !is_in_charset(str[i], charset))
			i++;
	}
	return (elem_count);
}

static int	strlen_til_sep(char *str, char *charset)
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

static char	*save_str(char *str, char *charset)
{
	int		str_len;
	int		i;
	char	*arr_word;

	i = 0;
	str_len = strlen_til_sep(str, charset);
	arr_word = malloc((str_len + 1) * sizeof(char));
	if (arr_word == NULL)
		return (NULL);
	while (i < str_len)
	{
		arr_word[i] = str[i];
		i++;
	}
	arr_word[i] = '\0';
	return (arr_word);
}

char	**ft_shellsplit(char *str, char *charset)
{
	char	**breakdown;
	int		i;
	int		token_len;

	i = 0;
	if (str == NULL)
		return (NULL);
	printf("Count = %d\n", count_strs(str, charset));
	breakdown = malloc(sizeof(char *) * (count_strs(str, charset) + 1));
	if (breakdown == NULL)
		return (NULL);
	while (*str)
	{
		while (*str && is_in_charset(*str, WHITESPACE))
			str++;
		if (*str)
		{
			token_len = strlen_til_sep(str, charset);
			breakdown[i] = save_str(str, charset);
			str += token_len;
			i++;
		}
	}
	breakdown[i] = 0;
	return (breakdown);
}
