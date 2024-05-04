/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:21:36 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/03 18:21:53 by smuravyev        ###   ########.fr       */
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

/* int	main(int ac, char **av, char **envp)
{
	t_main	shell;
	ft_bzero(&shell, sizeof(t_main));
} */

int	main(void)
{
	char	*user_input;
	t_token	*breakdown;

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
			free_tokens(breakdown);
			break ;
		}
		breakdown = lex_input(user_input);
		//parser(breakdown);
		if (!breakdown)
			return (1);
		free(user_input);
		free_tokens(breakdown);
		//int i = -1;
		/* while (breakdown[++i])
		{
			printf("(%s)-->", breakdown[i]);
		} */
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


/* 

1) Create a "structure" that will be passed everywhere
	a) it will need to point to structs that contain parsing, tokens, cmd tables and prelim
2) Ensure to store necessary information such as **envp
3) Find a logical way to get the information over through to lexer function and parser function
4) PARSING
	a) Go through each word and check with access, if the first word is not a valid command stop exec (?)
	b) Everything between first cmd and first pipe are args
	c) check how to handle redirections and here_doc.. 
	d) deliver a linked list that will look like this:
		| char** [cmd0, arg0, arg1, etc.]
		| OR
		| t_list cmd_tbl cmd0 ---> arg0 ---> arg1 ---> etc.
		| where I will always store the type of token and index
		| e.g "cat test.txt | wc -l" would look like this
		|  _____________________________         ______        ______________________
		| | cat ---> test.txt ---> NULL | --->  | >    | ---> | wc ---> -l ---> NULL | ---> NULL
		| | CMD      ARG                |       | PIPE |      | CMD      ARG         |
		| | 0                           |       | 1    |      | 2                    |
		|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         ~~~~~~        ~~~~~~~~~~~~~~~~~~~~~~
		|  typedef struct s_cmd_table
		|  {
		|   	struct t_cmd       *cmds;
		|       int          	   index;
		|       struct s_cmd_table *next;
		|  } t_cmd_table;
		|
		|  typedef struct s_cmds
		|  {
		|		char			   *word;
		|       t_type             type;
		|       int                needs_expansion;
		|       struct s_cmd       *next;
		|       struct s_cmd       *prev;
		|  }
	e) attempt simple execution
	




 */