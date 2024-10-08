/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:01:17 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/25 14:28:35 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline_first(t_cmds *cmds, pid_t *cpids, t_main *shell)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		handle_redirection(cmds);
		close_first_child(fds);
		exit(execute_cmd(cmds, shell, STDOUT_FILENO));
	}
	add_pid(pid, cpids);
	close_first_parent(fds);
	return (fds[0]);
}

int	exec_pipeline_last(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (cmds->prev->cmd_grp)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				ft_fprintf(STDERR_FILENO, "Child Dup STDIN last pipe\n");
				exit(EXIT_FAILURE);
			}
		}
		handle_redirection(cmds);
		close_fdin_last_child(fd_in);
		exit(execute_cmd(cmds, shell, STDOUT_FILENO));
	}
	add_pid(pid, cpids);
	close_fdin_last_parent(fd_in);
	return (-1);
}

int	exec_pipeline_middle(t_cmds *cmds, int fd_in, pid_t *cpids, t_main *shell)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		handle_redirection(cmds);
		close_middle_child(fds, fd_in);
		exit(execute_cmd(cmds, shell, STDOUT_FILENO));
	}
	add_pid(pid, cpids);
	close_middle_parent(fds, fd_in);
	return (fds[0]);
}

void	piping(t_cmds *tmp, pid_t *cpids, int *fd_in, t_main *shell)
{
	if (tmp->cmd_grp && tmp->cmd_grp[0])
	{
		if (!tmp->prev && !tmp->next)
		{
			if (!tmp->is_builtin)
				exec_single(tmp, cpids, shell);
			else
				exec_single_builtin(tmp, shell);
		}
		else if (!tmp->prev)
			*fd_in = exec_pipeline_first(tmp, cpids, shell);
		else if (!tmp->next)
			*fd_in = exec_pipeline_last(tmp, *fd_in, cpids, shell);
		else
			*fd_in = exec_pipeline_middle(tmp, *fd_in, cpids, shell);
	}
}
