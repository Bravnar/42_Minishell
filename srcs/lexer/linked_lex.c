/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:21:47 by smuravye          #+#    #+#             */
/*   Updated: 2024/05/03 15:54:46 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_space_bool(t_token *t, char *base, char *start, int len)
{
	int start_i;
	int	end_i;

	start_i = start - base;
	end_i = start_i + len;
	
	if (start_i > 0 && ft_strchr(WHITESPACE, start[start_i - 1]))
	{
		printf("im in condition 1\n");
		t->has_space_before = 1;
	}
	else if (start[end_i] && ft_strchr(WHITESPACE, start[end_i]))
	{
		printf("im in condition 2\n");
		t->has_space_after = 1;
	}
}

char	*handle_quote(char **cmd, t_parse *px)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	px->len = 1;
	if (tmp[1] == px->q_char)
		px->len = 2;
	else
	{
		while (tmp[px->len] != px->q_char || px->len == 1)
			px->len++;
		px->len++;
	}
	result = ft_substr(tmp, 0, px->len);
	*cmd += px->len;
	px->q_char = 0;
	return (result);
}

void	tokenize_input(t_parse *p, t_token **t, char *charset)
{
	char	*cur;
	char	*token;
	// t_token	*new_t;

	if (!p->work_line)
		return ;
	cur = p->work_line;
	while (*cur)
	{
		while (*cur && ft_strchr(WHITESPACE, *cur))
			cur++;
		if (!p->q_char && ft_strchr(QUOTES, *cur))
		{
			p->q_char = *cur;
			/* new_t = new_token(handle_quote(&cur, p));
			check_space_bool(new_t, p->work_line, cur, p->len);
			add_token(t, new_t); */
			add_token(t, new_token(handle_quote(&cur, p)));
		}
		else
		{
			p->token_len = strlen_til_sep(cur, charset);
			// check_space_bool(*t, p->work_line, cur, p->token_len);
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
	print_list(&head);
	return (head);
}
