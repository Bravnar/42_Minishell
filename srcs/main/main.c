/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bravnar <bravnar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:59:58 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/05 08:59:44 by bravnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;
	
	lex = shell->l;
	while (true)
	{
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		lexer(lex);
		// parser(shell);
		free(lex->input);
		free_tokens(lex->link);
		lex->link = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;
	
	(void)	ac;
	(void)	av;
	shell = init_structs(envp);
	gameplay_loop(shell);
}