/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 22/06/2024 17:19:52 by smuravye          #+#    #+#             */
/*   Updated: 24/06/2024 11:03:53 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_one(t_err code, char *file, t_main *shell)
{
	(void) file;
	if (code == BAD_QUOTES)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, QUOTES_ERR);
	else if (code == BAD_REDIR_APP)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, APPEND_ERR);
	else if (code == BAD_REDIRS_NL)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, NEWLINE_ERR);
	else if (code == BAD_PIPES)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, PIPE_ERR);
	else if (code == BAD_REDIR_HD)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, HEREDOC_SIGN_ERR);
	else if (code == BAD_REDIR_IN)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, REDIR_IN_ERR);
	else if (code == BAD_REDIR_OUT)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, REDIR_OUT_ERR);
	else if (code == FORB_CHAR)
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, SIMPLE_SYNTAX);
	set_env(&shell->env, "?", "2", 777);
}

void	errors_two(t_err code, char *file, t_main *shell)
{
	if (code == NO_INFILE)
		ft_fprintf(STDERR_FILENO,
			RED"minishell: %s: No such file or directory\n"RESET, file);
	else if (code == PERM_DENIED)
		ft_fprintf(STDERR_FILENO, RED"minishell: %s: Permission denied\n"RESET,
			file);
	else if (code == EXPORT_ERR)
		ft_fprintf(STDERR_FILENO,
			RED"%s%s: %s\n"RESET, MSHELL, file, EXPORT_SIGN);
	set_env(&shell->env, "?", "1", 777);
}

void	error_handler(t_err code, char *file, t_main *shell)
{
	if (code < 9)
		errors_one(code, file, shell);
	else if (code < 12)
		errors_two(code, file, shell);
	else
	{
		if (code == IS_DIR)
			ft_fprintf(STDERR_FILENO, RED"minishell: %s: Is a directory\n"RESET,
				file);
		else if (code == NO_COMMAND)
			ft_fprintf(STDERR_FILENO,
				RED"minishell: %s: command not found\n"RESET,
				file);
	}
}

/* void	error_handler(t_err code, char *file, t_main *shell)
{
	if (code == BAD_QUOTES) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, QUOTES_ERR);
	else if (code == BAD_REDIR_APP) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, APPEND_ERR);
	else if (code == BAD_REDIRS_NL) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, NEWLINE_ERR);
	else if (code == BAD_PIPES) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, PIPE_ERR);
	else if (code == BAD_REDIR_HD) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, HEREDOC_SIGN_ERR);
	else if (code == BAD_REDIR_IN) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, REDIR_IN_ERR);
	else if (code == BAD_REDIR_OUT) // error code 2
		ft_fprintf(STDERR_FILENO, RED"%s%s\n"RESET, MSHELL, REDIR_OUT_ERR);
	else if (code == FORB_CHAR) // error code 2
		ft_fprintf(shell->err, RED"%s%s\n"RESET, MSHELL, SIMPLE_SYNTAX);
	else if (code == NO_INFILE) // error code 1
		ft_fprintf(shell->err,
			RED"minishell: %s: No such file or directory\n"RESET, file);
	else if (code == PERM_DENIED) // error code 1
		ft_fprintf(STDERR_FILENO, RED"minishell: %s: Permission denied\n"RESET,
			file);
	else if (code == IS_DIR) // error code 126
		ft_fprintf(STDERR_FILENO, RED"minishell: %s: Is a directory\n"RESET,
			file);
	else if (code == NO_COMMAND) // error code 127
		ft_fprintf(STDERR_FILENO, RED"minishell: %s: command not found\n"RESET,
			file);
} */
