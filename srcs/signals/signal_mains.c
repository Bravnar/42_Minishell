/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_mains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:21:43 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 15:21:57 by smuravye         ###   ########.ch       */
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

void	sigaction_main(t_main *shell)
{
	struct sigaction	s;

	(void) shell;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	s.sa_handler = main_sigint_handler;
	sigaction(SIGINT, &s, NULL);
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
	s.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &s, NULL);
}

void	sigaction_proc(void)
{
	struct sigaction	s;

	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	s.sa_handler = SIG_DFL;
	sigaction(SIGINT, &s, NULL);
	s.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &s, NULL);
	s.sa_handler = handle_sigpipe;
	sigaction(SIGPIPE, &s, NULL);
}
