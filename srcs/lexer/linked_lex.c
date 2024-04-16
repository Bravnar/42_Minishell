/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:21:47 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/16 19:11:28 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quote(char **cmd, t_parse *px)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	px->len = 0;
	while (tmp[px->len] != px->q_char)
		px->len++;
	result = ft_substr(tmp, 0, px->len);
	*cmd += px->len + 1;
	px->q_char = 0;
	return (result);
}

void	tokenize_input(t_parse *p, t_token **t, char *charset)
{
	char	*cur;
	char	*token;

	if (!p->work_line)
		return ;
	cur = p->work_line;
	while (*cur)
	{
		while (*cur && ft_strchr(WHITESPACE, *cur))
			cur++;
		if (!p->q_char && ft_strchr(QUOTES, *cur))
		{
			p->q_char = *cur++;
			//check_quotebool(); --> need to add p->quotebool helpful for expansion later TO DO
			add_token(t, new_token(handle_quote(&cur, p)));
		}
		else
		{
			p->token_len = strlen_til_sep(cur, charset);
			token = ft_strndup(cur, p->token_len);
			add_token(t, new_token(token));
			free(token);
			cur += p->token_len;
		}
	}
}

t_token	*lex_input(char *input)
{
	t_parse	p;
	t_token	*head;

	ft_bzero(&p, sizeof(t_parse));
	head = NULL;
	p.work_line = ft_strtrim(input, WHITESPACE);
	if (check_quotes(p.work_line, &p.quotes))
	{
		printf(RED"Quotes issue detected\n"RESET);
		return (NULL);
	}
	tokenize_input(&p, &head, SPECIAL_W_SPACE);
	//check_after(); TO DO
	print_list(&head);
	return (head);
}
