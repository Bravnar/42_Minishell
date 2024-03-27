/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:57:04 by smuravyev         #+#    #+#             */
/*   Updated: 2024/03/27 14:19:11 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(const char *str)
{	
	if (!ft_strncmp(str, "echo", 4))
	{
		str += 4;
		while(*str == ' ')
			str++;
		ft_printf("%s\n", str);
	}
}

int	main(void)
{
	char *user_input;

	user_input = NULL;
	while (1)
	{
		user_input = readline(PROMPT);
		if (user_input == NULL)
			break ;
		if (user_input[0])
		add_history(user_input);
		ft_echo(user_input);
		if (strcmp(user_input, "Done") == 0)
		{
			free(user_input);
			break ;
		}
		free(user_input);
	}
	return (0);
}