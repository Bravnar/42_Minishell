/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:54:01 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 16:54:01 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subshell_handle(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	ft_fprintf(2, "\n");
	if (to_kill > 0)
		kill(to_kill, SIGINT);
	pid_for_signal(&to_restore);
}

int	is_vscode_terminal(t_main *shell)
{
	char	*vscode_var;

	vscode_var = get_env(&shell->env, "TERM_PROGRAM");
	if (!vscode_var || vscode_var[0] == '\0')
		return (2);
	if (!ft_strcmp(vscode_var, "vscode"))
	{
		free(vscode_var);
		return (3);
	}
	else
	{
		free(vscode_var);
		return (2);
	}
}

int	send_err_code(int *new_err)
{
	static int	err = 0;

	if (new_err)
	{
		err = *new_err;
	}
	return (err);
}

void	handle_sigpipe(int signum)
{
	(void) signum;
}

pid_t	pid_for_signal(pid_t *new)
{
	static pid_t	to_kill;

	if (new)
		to_kill = *new;
	return (to_kill);
}
