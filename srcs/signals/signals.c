/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:28 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 16:06:28 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	if (g_signal_received == HEREDOC_SIG)
		exit(130);
}

void	main_sigint_handler(int signum)
{
	int	err_code;

	err_code = 130;
	if (g_signal_received == NORMAL && signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		send_err_code(&err_code);
	}
	else if (g_signal_received == EXEC && signum == SIGINT)
		proc_sigint_handler(signum);
	else if (g_signal_received == EXEC && signum == SIGQUIT)
		proc_sigquit_handler(signum);
}

void	proc_sigint_handler(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;
	int		err_code;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	err_code = 130;
	write(STDOUT_FILENO, "\n", 1);
	if (g_signal_received == EXEC)
	{
		if (to_kill > 0)
			kill(to_kill, SIGINT);
		send_err_code(&err_code);
	}
	pid_for_signal(&to_restore);
}

void	proc_sigquit_handler(int signum)
{
	pid_t	to_kill;
	pid_t	to_restore;
	int		err_code;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	to_restore = -1;
	err_code = 131;
	write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	if (g_signal_received == EXEC)
	{
		if (to_kill > 0)
		{
			kill(to_kill, SIGQUIT);
			waitpid(to_kill, NULL, 0);
		}
		send_err_code(&err_code);
	}
	pid_for_signal(&to_restore);
}

/* void	main_sigint_handler(int	signum)
{
	pid_t	to_kill;
	pid_t	to_restore;

	(void) signum;
	to_kill = pid_for_signal(NULL);
	if (g_signal_received == NORMAL)
		handle_zero();
	else if (g_signal_received == EXEC)
		handle_two(to_kill);
	pid_for_signal(&to_restore);
} */
		// exit(131);