/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 24/06/2024 08:06:42 by hmorand           #+#    #+#             */
/*   Updated: 24/06/2024 09:09:50 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pid(pid_t pid, pid_t *cpids)
{
	int				i;

	i = -1;
	while (cpids[++i])
		;
	cpids[i++] = pid;
	pid_for_signal(&pid);
	cpids[i] = 0;
}

void	determine_err(t_main *shell, int status)
{
	char	*convert_status;
	int		err;
	int		reset;

	reset = 0;
	convert_status = ft_itoa(status % 255);
	set_env(&shell->env, "?", convert_status, 777);
	err = send_err_code(NULL);
	free(convert_status);
	convert_status = NULL;
	if (err == 130 || err == 131)
	{
		convert_status = ft_itoa(err);
		set_env(&shell->env, "?", convert_status, 777);
		free(convert_status);
		send_err_code(&reset);
	}
}

int	wait_for_children(pid_t *cpids, t_main *shell)
{
	int		status;
	int		i;

	status = 0;
	i = -1;
	if (cpids[0] == 0)
		return (0);
	while (cpids[++i])
	{
		waitpid(cpids[i], &status, 0);
	}
	determine_err(shell, status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}
