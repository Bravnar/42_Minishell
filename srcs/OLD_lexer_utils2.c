/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:00:45 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/11 16:52:18 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_space(char **cmd, t_parse *p)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	p->len = 0;
	while (tmp[p->len] != ' ' && tmp[p->len] != '\0')
		p->len++;
	result = ft_substr(tmp, 0, p->len);
	*cmd += p->len;
	return (result);
}

void	skip_whitespace(char *str)
{
	while (*str && is_in_charset(*str, WHITESPACE))
		str++;
}

char	**ft_shellsplit(t_parse *p, char *str, char *charset)
{
	char	**ret;
	int		i;
	int		token_len;

	if (str == NULL)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_split(str, charset) + 1));
	if (ret == NULL)
		return (NULL);
	while (*str)
	{
		skip_whitespace(str);
		if (!p->q_char && ft_strchr(QUOTES, *str))
		{
			p->q_char = *str++;
			ret[i] = handle_quote()
		}
		handle_rest(&token_len, str, charset, &ret[i]);
		str += token_len;
	}
	ret[i] = 0;
	return (ret);
}
