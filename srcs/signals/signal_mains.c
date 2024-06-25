/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_mains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:25:39 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 16:42:14 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigaction_hd(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	s.sa_handler = heredoc_sigint_handler;
	sigaction(SIGINT, &s, NULL);
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
	s.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &s, NULL);
}

void	sigaction_main(t_main *shell, int is_blocking)
{
	struct sigaction	s;
	int					shlvl;

	(void) shell;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	shlvl = ft_atoi(get_env(&shell->env, "SHLVL"));
	if (shlvl <= is_vscode_terminal(shell))
	{
		s.sa_handler = main_sigint_handler;
		sigaction(SIGINT, &s, NULL);
		if (is_blocking)
			s.sa_handler = proc_sigquit_handler;
		else
			s.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &s, NULL);
	}
	else
	{
		s.sa_handler = SIG_DFL;
		sigaction(SIGINT, &s, NULL);
		s.sa_handler = SIG_DFL;
		sigaction(SIGQUIT, &s, NULL);
	}
}

		// s.sa_handler = handle_sigpipe;
		// sigaction(SIGPIPE, &s, NULL);
void	sigaction_proc(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	s.sa_handler = SIG_DFL;
	sigaction(SIGINT, &s, NULL);
	s.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &s, NULL);
	s.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &s, NULL);
}
