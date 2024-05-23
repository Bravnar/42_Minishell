#include "minishell.h"

t_lex	*init_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	return (lex);
}

t_main	*init_structs(char **envp)
{
	t_main	*shell;

	shell = ft_calloc(1, sizeof(t_main));
	if (shell)
	{
		shell->l = init_lex();
		shell->envp = envp;
		shell->has_env = 1;
		shell->prompt = NULL;
		populate_envp(shell);
		shell->username = get_env(&shell->env, "$USER");
		// if (shell->username == NULL)
		// 	shell->prompt = BOLD_YELLOW FACE BOLD_WHITE THROW RESET;
	}
	return (shell);
}
