#include "minishell.h"

void	print_error(char *err)
{
	while (*err)
		write(STDERR_FILENO, err++, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error_handler(t_err code, char *file, t_main *shell)
{
	if (code == BAD_QUOTES) // error code 2
		ft_fprintf(shell->err,
			RED"minishell: Mismatched quotation marks.\n"RESET);
	else if (code == BAD_REDIRS) // error code 2
		ft_fprintf(shell->err, \
			RED"minishell: syntax error near unexpected token '>' or '<'.\n"RESET);
	else if (code == BAD_REDIRS_NL) // error code 2
		ft_fprintf(shell->err,
			RED"minishell: syntax error near unexpected token 'newline'\n"RESET);
	else if (code == BAD_PIPES) // error code 2
		ft_fprintf(shell->err,
			RED"minishell: syntax error near unexpected token '|'\n"RESET);
	else if (code == NO_INFILE) // error code 2
		ft_fprintf(shell->err,
			RED"minishell: %s: No such file or directory\n"RESET, file);
	else if (code == PERM_DENIED) // error code 1
		ft_fprintf(shell->err, RED"minishell: %s: Permission denied\n"RESET,
			file);
	else if (code == IS_DIR) // error code 126
		ft_fprintf(shell->err, RED"minishell: %s: Is a directory\n"RESET,
			file);
	else if (code == NO_COMMAND) // error code 127
		ft_fprintf(shell->err, RED"minishell: %s: command not found\n"RESET,
			file);
}
