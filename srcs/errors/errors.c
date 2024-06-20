#include "minishell.h"

void	print_error(char *err)
{
	while (*err)
		write(STDERR_FILENO, err++, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error_handler(t_err code, char *file, t_main *shell)
{
	if (code == BAD_QUOTES)
		ft_fprintf(shell->err,
			RED"minishell: Mismatched quotation marks.\n"RESET);
	else if (code == BAD_REDIRS)
		ft_fprintf(shell->err, \
			RED"minishell: syntax error near unexpected token '>' or '<'.\n"RESET);
	else if (code == BAD_REDIRS_NL)
		ft_fprintf(shell->err,
			RED"minishell: syntax error near unexpected token 'newline'\n"RESET);
	else if (code == BAD_PIPES)
		ft_fprintf(shell->err,
			RED"minishell: syntax error near unexpected token '|'\n"RESET);
	else if (code == NO_INFILE)
		ft_fprintf(shell->err,
			RED"minishell: %s: No such file or directory\n"RESET, file);
	else if (code == PERM_DENIED)
		ft_fprintf(shell->err, RED"minishell: %s: Permission denied\n"RESET,
			file);
	else if (code == IS_DIR)
		ft_fprintf(shell->err, RED"minishell: %s: Is a directory\n"RESET,
			file);
	else if (code == NO_COMMAND)
		ft_fprintf(shell->err, RED"minishell: %s: command not found\n"RESET,
			file);
}
