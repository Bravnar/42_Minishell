/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:49:33 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/25 08:58:24 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(int fds[2], t_files *file)
{
	char	*in;

	if (close(fds[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - Close read end pipe heredoc\n");
		exit(EXIT_FAILURE);
	}
	sigaction_hd();
	while (1)
	{
		in = readline("> ");
		if (!in || !ft_strncmp(in, file->file_name, ft_strlen(file->file_name)))
		{
			free(in);
			break ;
		}
		ft_fprintf(fds[1], "%s\n", in);
		free(in);
	}
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - Close write end pipe heredoc\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

t_files	*early_exit(int fds[2])
{
	g_signal_received = NORMAL;
	if (close(fds[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Parent - Close read end \
			pipe heredoc early exit");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	parse_heredoc(t_files *file, int fds[2], t_main *shell)
{
	char	*final;
	char	*in;
	char	*full_input;

	full_input = ft_strdup("");
	in = ft_strdup("");
	while (in && ft_strncmp(in, file->file_name, ft_strlen(file->file_name)))
	{
		full_input = ft_better_join(full_input, in, 1);
		in = get_next_line(fds[0]);
	}
	free(file->file_name);
	final = var_replace(full_input, shell);
	if (final)
		file->file_name = ft_strdup(final);
	else
		file->file_name = ft_strdup("");
	g_signal_received = NORMAL;
	free(full_input);
	free(in);
	free(final);
}

void	setup_parent_heredoc(pid_t *pid, int *status, int fds[2])
{
	pid_for_signal(pid);
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Parent - close write end - pipe heredoc");
		exit(EXIT_FAILURE);
	}
	waitpid(*pid, status, 0);
}

t_files	*extract_heredoc(t_files *file, t_main *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	g_signal_received = HEREDOC_SIG;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		heredoc_child(pipefd, file);
	else
	{
		setup_parent_heredoc(&pid, &status, pipefd);
		if (WIFSIGNALED(status))
			early_exit(pipefd);
		determine_err(shell, status);
		parse_heredoc(file, pipefd, shell);
	}
	return (file);
}
