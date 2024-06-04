#include "minishell.h"

void	print_error(char *err)
{
	while (*err)
		write(STDERR_FILENO, err++, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error_handler(t_err code, char *file)
{
	if (code == BAD_QUOTES)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: Mismatched quotation marks."RESET);
	else if (code == BAD_REDIRS)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: syntax error near \
				unexpected token '>' or '<'."RESET);
	else if (code == BAD_REDIRS_NL)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: syntax error near unexpected token 'newline'"RESET);
	else if (code == BAD_PIPES)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: syntax error near unexpected token '|'"RESET);
	else if (code == NO_INFILE)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: %s: No such file or directory"RESET, file);
	else if (code == PERM_DENIED)
		ft_fprintf(STDERR_FILENO, RED"minishell: %s: Permission denied"RESET,
			file);
}
