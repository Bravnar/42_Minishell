/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:56:20 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/06 14:19:54 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	count_args(const char *cmd)
{
	int	count;
	int	in_quotes;

	count = 0;
	if (!cmd)
		return (count);
	in_quotes = 0;
	while (*cmd == ' ')
		cmd++;
	while (*cmd)
	{
		if (!in_quotes && (*cmd == '\'' || *cmd == '\"'))
			in_quotes = *cmd;
		else if (in_quotes && (*cmd == in_quotes))
			in_quotes = 0;
		else if (*cmd == ' ' && !in_quotes)
		{
			count++;
			while (*cmd == ' ')
				cmd++;
			continue ;
		}
		cmd++;
	}
	return (count + 1);
} */

int	count_args(const char *str)
{
	int	count;
	int	in_quotes;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		if (!in_quotes && ft_strchr(QUOTES, *str))
			in_quotes = *str;
		else if (in_quotes && (*str == in_quotes))
			in_quotes = 0;
		else if (*str == ' ' && !in_quotes)
		{
			count++;
			while (*str == ' ')
				str++;
			continue ;
		}
		else if (!in_quotes && ft_strchr(SPECIAL, *str) && *str + 1 != ' ' && *str - 1 != ' ')
		{
			count++;
			/* if (!(str[1]) && ft_strchr(SPECIAL, str[1]) && *str == str[1])
				str++; */
		}
		str++;
	}
	return (count + 1);
}

char	*handle_special(t_parse *p)
{
	char	*result;

	result = calloc(2, sizeof(char));
	result[0] = *(p)->work_line;
	result[1] = '\0';
	p->work_line++;
	return (result);
}

char	*handle_quote(t_parse *p)
{
	char	*tmp;
	char	*result;

	tmp = p->work_line;
	p->len = 0;
	while (tmp[p->len] != p->q_char)
		p->len++;
	result = ft_substr(tmp, 0, p->len);
	p->work_line += p->len + 1;
	p->q_char = 0;
	return (result);
}

char	*handle_space(t_parse *p)
{
	char	*tmp;
	char	*result;

	tmp = p->work_line;
	p->len = 0;
	while (tmp[p->len] != ' ' && tmp[p->len] != '\0')
		p->len++;
	result = ft_substr(tmp, 0, p->len);
	p->work_line += p->len;
	return (result);
}

char	**lex(char *input)
{
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	p.work_line = ft_strtrim(input, WHITESPACE);
	p.count = count_args(p.work_line);
	printf("Count = %d\n", p.count);
	p.args_list = calloc(p.count + 1, sizeof(char *));
	while (*p.work_line)
	{
		while (ft_isspace(*p.work_line))
			p.work_line++;
		if (!p.q_char && (ft_strchr(QUOTES, *(p).work_line)))
		{
			p.q_char = *(p).work_line;
			p.work_line++;
		}
		if (p.q_char)
			p.args_list[p.i++] = handle_quote(&p);
		else if (!p.q_char && ft_strchr(SPECIAL, *(p).work_line))
			p.args_list[p.i++] = handle_special(&p);
		else if (!p.q_char && *(p).work_line)
			p.args_list[p.i++] = handle_space(&p);
	}
	p.args_list[p.i] = NULL;
	return (p.args_list);
}
