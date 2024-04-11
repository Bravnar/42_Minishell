/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:39:57 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/11 18:58:53 by smuravye         ###   ########.fr       */
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

void	skip_whitespace(char **str)
{
	while (**str && is_in_charset(**str, WHITESPACE))
		(*str)++;
}

int	count_split(t_parse *p, char *charset)
{
	(void) charset;
	p->count = 5;
	return (p->count);
}

char	**ft_supersplit(t_parse *p, char *charset)
{
	if (p->work_line == NULL)
		return (NULL);
	printf("Count: %d\n", count_args(p->work_line, charset));
	p->args = malloc(sizeof(char *) * (count_args(p->work_line, charset)));
	if (!p->args)
		return (NULL);
	while (*(p)->work_line)
	{
		skip_whitespace(&p->work_line);
		if (!p->q_char && ft_strchr(QUOTES, *(p)->work_line))
		{
			p->q_char = *(p)->work_line++;
			p->args[p->i] = handle_quote(&p->work_line, p);
		}
		else
		{
			p->token_len = strlen_til_sep(p->work_line, charset);
			p->args[p->i] = save_str(p->work_line, charset);
			p->work_line += p->token_len;
		}
		p->i++;
	}
	p->args[p->i] = NULL;
	return (p->args);
}

char	**lex(char *input)
{
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	p.work_line = ft_strtrim(input, WHITESPACE);
	p.args = ft_supersplit(&p, SPECIAL_W_SPACE);
	p.invalid_token = check_validity(p.args, SPECIAL);
	if (p.invalid_token)
		printf(RED"Token error detected\n"RESET);
	return (p.args);
}
