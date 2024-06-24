/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:06:30 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 09:06:30 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_middle_child(int fds[2], int fd_in)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Child - closing fd in - middle pipe\n");
			exit(EXIT_FAILURE);
		}
	}
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - closing write end - middle pipe");
		exit(EXIT_FAILURE);
	}
	if (close(fds[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - closing read en  - middle pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_middle_parent(int fds[2], int fd_in)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Parent - closing fd in - middle pipe\n");
			exit(EXIT_FAILURE);
		}
	}
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Parent - closing write end - middle pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_first_child(int fds[2])
{
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - closing write end - first pipe");
		exit(EXIT_FAILURE);
	}
	if (close(fds[0]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Child - closing read en  - first pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_first_parent(int fds[2])
{
	if (close(fds[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Parent - closing write end - first pipe");
		exit(EXIT_FAILURE);
	}
}
