/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:55:09 by smuravyev         #+#    #+#             */
/*   Updated: 2024/05/03 16:45:35 by smuravyev        ###   ########.fr       */
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

char	*handle_quote(t_lex_info *info)
{
	char	*tmp;
	char	*result;

	tmp = info->cur;
	info->len = 1;
	if (tmp[1] == info->q_char)
		info->len = 2;
	else
	{
		while (tmp[info->len] != info->q_char || info->len == 1)
			info->len++;
		info->len++;
	}
	result = ft_substr(tmp, 0, info->len);
	info->cur += info->len;
	info->q_char = 0;
	return (result);
	
}

void	tokenize_input(t_shell *main, t_lex_info *info, char *charset)
{
	if (!main->trimmed_input)
		return ;
	info->cur = main->trimmed_input;
	while (info->cur)
	{
		while (*info->cur && ft_strchr(WHITESPACE, *info->cur))
			info->cur++;
		if (!info->q_char && ft_strchr(QUOTES, *info->cur))
		{
			info->q_char = *info->cur;
			add_token(&main->lexems, new_token(handle_quote(info)));			
		}
		else
		{
			info->token_len = strlen_til_sep(info->cur, charset);
			info->token = ft_strndup(info->cur, info->token_len);
			add_token(&main->lexems, new_token(info->token));
			free(info->token);
			info->cur += info->token_len;
		}
	}
}

void	alt_lex(t_shell *main)
{
	t_lex	*head;
	
	head = NULL;
	main->lexems = head;
	main->trimmed_input = ft_strtrim(main->user_input, WHITESPACE);
	/* if (check_input(main->trimmed_input))
		return ; //error handling path */
	tokenize_input(main, main->lex_info, SPECIAL_W_SPACE);
	print_list(&main->lexems);
}