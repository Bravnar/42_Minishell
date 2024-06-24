/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:40 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 17:52:13 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile(char *infile, t_main *shell)
{
	int	fd;

	fd = open(infile, O_RDONLY, 00644);
	if (fd == -1)
	{
		if (access(infile, F_OK) == 0)
			shell->err_code = PERM_DENIED;
		else
			shell->err_code = NO_INFILE;
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

t_files *extract_heredoc(t_files *file, t_main *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*final;
	char	*input;
	char	*full_input;

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
	{
		close(pipefd[0]);
		setup_heredoc_signals();
		input = ft_strdup("");
		while (1)
		{
			input = readline("> ");
			if (!input || !ft_strncmp(input, file->file_name, ft_strlen(file->file_name)))
			{
				free(input);
				break;
			}
			ft_fprintf(pipefd[1], "%s\n", input);
			free(input);
		}
		// while (!input || ft_strncmp(input, file->file_name, ft_strlen(file->file_name)))
		// {
		// 	// write(STDOUT_FILENO, "> ", 2);
		// 	free(input);
		// 	input = readline("> ");
		// 	// input = get_next_line(STDIN_FILENO);
		// 	ft_fprintf(pipefd[1], "%s\n", input);
		// }
		// free(input);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		pid_for_signal(&pid);
		full_input = ft_strdup("");
		input = ft_strdup("");
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		printf("Child process finished, status: %d\n", status);
		printf("Child process finished WIFSIGNALED: %d\n", WIFSIGNALED(status));
		printf("Child process finished WTERMSIG: %d\n", WTERMSIG(status));
		if (WIFSIGNALED(status))  // MODIFIED: Check if child was terminated by SIGINT
        {
			printf("Im here\n");
            g_signal_received = NORMAL;
            close(pipefd[0]);
            free(full_input);
            return file;  // MODIFIED: Return early if Ctrl-C was pressed
        }
		determine_err(shell, status);
		while (input && ft_strncmp(input, file->file_name, ft_strlen(file->file_name)))
		{
			full_input = ft_better_join(full_input, input, 1);
			input = get_next_line(pipefd[0]);
		}
		free(file->file_name);
		final = var_replace(full_input, shell);
		if (final)
			file->file_name = ft_strdup(final);
		else
			file->file_name = ft_strdup("");
		g_signal_received = NORMAL;
		free(full_input);
		free(input);
		free(final);
	}
	return file;
}


/* t_files	*extract_heredoc(t_files *file, t_main *shell)
{
	char	*line;
	char	*input;
	char	*final;

	g_signal_received = HEREDOC_SIG;
	line = ft_strdup("");
	input = ft_strdup("");
	while (ft_strncmp(input, file->file_name, ft_strlen(file->file_name)))
	{
		line = ft_better_join(line, input, 1);
		write(STDOUT_FILENO, "> ", 2);
		input = get_next_line(STDIN_FILENO);
	}
	free(file->file_name);
	final = var_replace(line, shell);
	if (final)
		file->file_name = ft_strdup(final);
	else
		file->file_name = ft_strdup("");
	free(line);
	free(final);
	free(input);
	return (file);
} */

int	check_outfile(char *outfile, t_main *shell, t_type t)
{
	int	fd;

	if (t == OUTFILE_APP)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
	{
		if (access(outfile, F_OK) == 0)
			shell->err_code = PERM_DENIED;
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_file(t_files *file, t_main *shell)
{
	if (file->type == INFILE)
	{
		if (check_infile(file->file_name, shell))
			return (EXIT_FAILURE);
	}
	else if (file->type == OUTFILE || file->type == OUTFILE_APP)
	{
		if (check_outfile(file->file_name, shell, file->type))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_files(t_main *shell, t_cmds *cmds)
{
	t_cmds	*temp;
	t_files	*tmp_file;

	temp = cmds;
	if (!temp)
		return (EXIT_FAILURE);
	while (temp)
	{
		tmp_file = temp->files;
		while (tmp_file)
		{
			if (check_file(tmp_file, shell))
				return (error_handler(shell->err_code,
						tmp_file->file_name, shell), EXIT_FAILURE);
			else if (tmp_file->type == INFILE)
				temp->last_infile = tmp_file;
			else if (tmp_file->type == HEREDOC_END)
				temp->last_infile = extract_heredoc(tmp_file, shell);
			if (tmp_file->type == OUTFILE || tmp_file->type == OUTFILE_APP)
				temp->last_outfile = tmp_file;
			tmp_file = tmp_file->next;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
