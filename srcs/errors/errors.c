#include "minishell.h"

void	print_error(char *err)
{
	while (*err)
		write(STDERR_FILENO, err++, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error_handler(t_err code)
{
	if (code == BAD_QUOTES)
		print_error(RED"minishell: Mismatched quotation marks."RESET);
	else if (code == BAD_REDIRS)
		print_error(RED"minishell: syntax error near unexpected token '>' or '<'."RESET);
	else if (code == BAD_REDIRS_NL)
		print_error(RED"minishell: syntax error near unexpected token 'newline'"RESET);
	else if (code == BAD_PIPES)
		print_error(RED"minishell: syntax error near unexpected token '|'"RESET);
}