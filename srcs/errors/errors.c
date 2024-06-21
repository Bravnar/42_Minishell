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
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, QUOTES_ERR);
	else if (code == BAD_REDIR_APP) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, APPEND_ERR);
	else if (code == BAD_REDIRS_NL) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, NEWLINE_ERR);
	else if (code == BAD_PIPES) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, PIPE_ERR);
	else if (code == BAD_REDIR_HD) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, HEREDOC_SIGN_ERR);
	else if (code == BAD_REDIR_IN) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, REDIR_IN_ERR);
	else if (code == BAD_REDIR_OUT) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, REDIR_OUT_ERR);
	else if (code == FORB_CHAR) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, SIMPLE_SYNTAX);
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
