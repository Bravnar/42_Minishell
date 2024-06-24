/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 08:06:42 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 16:42:03 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmds *cmds, t_main *shell, int fd)
{
	int	err_code;

	if (cmds->is_builtin)
		exit(builtins(cmds, shell, fd));
	if (!cmds->cmd_grp)
	{
		if (cmds->last_infile || cmds->last_outfile)
		{
			ft_fprintf(STDERR_FILENO, "Exiting cause no command\n");
			return (EXIT_SUCCESS);
		}
	}
	err_code = is_bad_command(cmds, shell);
	if (err_code)
		return (error_handler(shell->err_code,
				cmds->cmd_grp[0], shell), err_code);
	shell->envp = back_to_array(shell->env);
	execve(cmds->path, cmds->cmd_grp, shell->envp);
	ft_free_arr(shell->envp);
	perror("Execve");
	return (EXIT_FAILURE);
}

int	exec_single(t_cmds *cmds, pid_t *cpids, t_main *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		handle_redirection(cmds);
		exit(execute_cmd(cmds, shell, STDOUT_FILENO));
	}
	add_pid(pid, cpids);
	return (-1);
}

int	execute(t_cmds *cmds, t_main *shell)
{
	t_cmds	*tmp;
	int		fd_in;
	pid_t	*cpids;

	set_env(&shell->env, "?", "0", 777);
	g_signal_received = EXEC;
	if (check_files(shell, cmds))
		return (EXIT_FAILURE);
	cpids = malloc(sizeof(pid_t) * (cmd_size(cmds) + 1));
	if (!cpids)
		return (EXIT_FAILURE);
	set_underscore(cmds, shell);
	cpids[0] = 0;
	tmp = cmds;
	fd_in = -1;
	while (tmp)
	{
		piping(tmp, cpids, &fd_in, shell);
		tmp = tmp->next;
	}
	wait_for_children(cpids, shell);
	free(cpids);
	g_signal_received = NORMAL;
	return (EXIT_SUCCESS);
}
