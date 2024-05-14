#include "minishell.h"

int	lexer(t_lex	*l)
{
	l->trim = ft_strtrim(l->input, WHITESPACE);
	reset_quotes(l);
	if (check_quotes(l))
		return (error_handler(l->err_code), 1);
	lex_input(l, SPECIAL_W_SPACE);
	if (check_redirs(l) || check_pipes(l))
		return (error_handler(l->err_code), 1);
	fill_info(l);
	print_list(&l->link);
	return (0);
}
