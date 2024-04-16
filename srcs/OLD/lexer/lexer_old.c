/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:37:26 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/05 14:43:49 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(const char *cmd)
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
}

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

char	*handle_quote(char **cmd, t_parse *p)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	p->len = 0;
	while (tmp[p->len] != p->q_char)
		p->len++;
	result = ft_substr(tmp, 0, p->len);
	*cmd += p->len + 1;
	p->q_char = 0;
	return (result);
}

char	**mh_lex(char *u_input)
{
	t_parse	p;

	p.i = 0;
	p.q_char = 0;
	p.count = count_args(u_input);
	printf("count: %d\n", p.count);
	p.args_list = malloc(sizeof(char *) * (p.count + 1));
	if (!p.args_list)
		return (NULL);
	while (*u_input)
	{
		while (ft_isspace(*u_input))
			u_input++;
		if (!p.q_char && (*u_input == 34 || *u_input == 39))
		{
			p.q_char = *u_input;
			u_input++;
		}
		if (p.q_char)
			p.args_list[p.i++] = handle_quote(&u_input, &p);
		else if (!p.q_char && *u_input)
			p.args_list[p.i++] = handle_space(&u_input, &p);
	}
	p.args_list[p.i] = NULL;
	return (p.args_list);
}
/* IMPORTANT:
	Need to add a thing that handles \" \' \$ etc" */