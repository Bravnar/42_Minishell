/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:43:34 by smuravyev         #+#    #+#             */
/*   Updated: 2024/05/03 16:43:28 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ac(int ac)
{
	if (ac > 1)
	{
		write(2, "AC_Error\n", 9);
		return ;
	}
	return ;
}

char	*create_prompt(t_shell *main)
{
	(void) main;
	return (PROMPT);
}

void	shell_loop(t_shell *main)
{
	while (1)
	{
		main->user_input = readline(main->prompt);
		if (main->user_input == NULL)
			break ;
		if (main->user_input[0])
			add_history(main->user_input);
		alt_lex(main);
		if (!main->lexems)
			return ;
		free(main->user_input);
		free_tokens(main->lexems);
	}
	return ;
}

void	init_shell(t_shell *main, char **envp)
{
	main = ft_calloc(1, sizeof(t_shell));
	if (!main)
		return ;
	//main->env = set_envp(envp); //to write
	main->env = envp;
	main->prompt = create_prompt(main);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_shell	main;

	check_ac(ac);
	init_shell(&main, envp);
	shell_loop(&main);
	//cleanup();
	return (0);	
}