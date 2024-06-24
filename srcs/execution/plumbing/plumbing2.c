/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumbing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:06:41 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 09:06:41 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fdin_last_child(int fd_in)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Child - closing fd in - last pipe\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_fdin_last_parent(int fd_in)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Parent - closing fd in - last pipe\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_fdin_builtin(int fd_in)
{
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
		{
			ft_fprintf(STDERR_FILENO, "Builtin - closing fd in - last pipe\n");
			exit(EXIT_FAILURE);
		}
	}
}
