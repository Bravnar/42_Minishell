#include "minishell.h"

/* Quick function to initialize t_lex
   ft_calloc allows all bytes to be set to 0 or NULL */
t_lex	*init_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	return (lex);
}

/* Function to initialize the main structure
   Also calls the populate environment here! */
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
		set_env(&shell->env, "?", "0", 777);
		shell->username = get_env(&shell->env, "$USER");
		shell->home = get_env(&shell->env, "$HOME");
		shell->in = dup(STDIN_FILENO);
		shell->out = dup(STDOUT_FILENO);
		shell->err = dup(STDERR_FILENO);
	}
	return (shell);
}
