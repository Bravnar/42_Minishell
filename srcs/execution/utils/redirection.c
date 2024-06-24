/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:11:12 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 09:11:26 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(t_files *outfile)
{
	int	fd;

	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("Failed to open output file");
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2\n");
		exit(EXIT_FAILURE);
	}
}

int	redirect_heredoc(t_files *infile)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Pipe heredoc\n");
		exit(EXIT_FAILURE);
	}
	ft_fprintf(fds[1], "%s", infile->file_name);
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Closing write end pipe heredoc");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2 heredoc stdin\n");
		exit(EXIT_FAILURE);
	}
	if (close(fds[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Closing read end pipe heredoc");
		exit(EXIT_FAILURE);
	}
	return (STDIN_FILENO);
}

int	redirect_input(t_files *infile)
{
	int	fd;

	if (infile->type == HEREDOC_END)
		return (redirect_heredoc(infile));
	fd = open(infile->file_name, O_RDONLY);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, "Failed to open input file");
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(STDERR_FILENO, "dup2\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_redirection(t_cmds *cmd)
{
	if (cmd->last_infile)
		redirect_input(cmd->last_infile);
	if (cmd->last_outfile)
		redirect_output(cmd->last_outfile);
}
