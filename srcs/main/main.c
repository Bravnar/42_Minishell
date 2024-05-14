#include "minishell.h"

void	free_all(t_main *shell)
{
	if (shell->l->input)
	{
		free(shell->l->input);
		shell->l->input = NULL;
	}
	if (shell->l->trim)
	{
		free(shell->l->trim);
		shell->l->trim = NULL;
	}
	if (shell->l->link)
	{
		free_tokens(shell->l->link);
		shell->l->link = NULL;
	}
}

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;
	int		count = 0;

	lex = shell->l;
	while (count < 3)
	{
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		lexer(lex);
		if (lex->link)
		{
			if (!ft_strcmp(lex->link->value, "env"))
				print_envp(&shell->env);
		}
		free_all(shell);
		count++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;

	(void)	ac;
	(void)	av;
	shell = init_structs(envp);
	gameplay_loop(shell);
	free_main(shell);
}