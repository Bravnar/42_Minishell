/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:43:34 by smuravyev         #+#    #+#             */
/*   Updated: 2024/05/02 17:06:43 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ac(int ac)
{
	if (ac > 1)
	{
		write(2, "AC_Error\n", 9);
		return (1);
	}
	return (0);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return ;
	shell->env = envp;
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_shell	shell;
	if (check_ac(ac))
		return (0);
	init_shell(&shell, envp);
	int	i = -1;
	while (shell.env[++i])
		printf("%s\n", shell.env[i]);
	return (0);
}