/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:21:36 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/05 16:19:44 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	ft_echo(const char *str)
{
	if (!ft_strncmp(str, "echo ", 5))
	{
		str += 5;
		while (*str == ' ')
			str++;
		while (*str)
		{
			if (*str != '\'' && *str != '\"')
				write(1, str++, 1);
			else
				str++;
		}
		write(1, "\n", 1);
	}
}

int	main(void)
{
	char	*user_input;
	char    **breakdown;

	user_input = NULL;
	while (1)
	{
		user_input = readline(PROMPT);
		if (user_input == NULL)
			break ;
		if (user_input[0])
			add_history(user_input);
		//ft_echo(user_input);
		if (strcmp(user_input, "Done") == 0)
		{
			free(user_input);
			break ;
		}
		breakdown = mh_lex(user_input);
		free(user_input);
		int i = -1;
		while (breakdown[++i])
		{
			printf("(%s)-->", breakdown[i]);
		}
		printf("\n");
		
	}
	return (0);
}
/* 
Plan of action:
	1) Utilise a parser that is similar to the one done in pipex
	2) Find a way to store these variables (linked list?)
		a) Try to store user input split by spaces and or quotation marks
		b) Store in a linked list that will keep track of position and type
		c) Tokenize (???)
	3) Once stored, check if contents are cmd or arg or special character
	4) Handle according to infile, outfile, heredoc, pipe and/or simple execution

First idea:
	Use a similar parser to pipex to breakdown user input and store it in a linked list!
 */

/* 
Actual main should look something like this

int main (int ac, char **av, char **env)
{
	check_input();
	initialize_structs();
	parsing();
	execution();
	cleanup() or just dump_garbage();
}
 */