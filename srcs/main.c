/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:21:36 by hmorand           #+#    #+#             */
/*   Updated: 2024/03/27 20:21:36 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
