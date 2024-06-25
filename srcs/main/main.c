/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:24:42 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 16:24:42 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;

	lex = shell->l;
	while (1)
	{
		g_signal_received = NORMAL;
		terminal_prompt(shell);
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		receive_err(shell);
		if (!lexer(lex, shell))
		{
			check_builtins(shell->cmds);
			execute(shell->cmds, shell);
		}
		free_all(shell);
		clear_t_cmds(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;

	(void) ac;
	(void) av;
	shell = init_structs(envp);
	sigaction_main(shell, 0);
	gameplay_loop(shell);
	free_main(shell);
}
