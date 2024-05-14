#include "minishell.h"

t_llex	*init_llex(void)
{
	return (calloc(1, sizeof(t_llex)));
}

t_lex	*init_lex(void)
{
	t_lex	*lex;

	lex = calloc(1, sizeof(t_lex));
	return (lex);
}

/* t_tok	*init_tok(void)
{
	return (calloc(1, sizeof(t_tok)));
} */

t_cmds	*init_cmds(void)
{
	return (calloc(1, sizeof(t_cmds)));
}

t_main	*init_structs(char **envp)
{
	t_main	*shell;

	shell = ft_calloc(1, sizeof(t_main));
	if (shell)
	{
		shell->l = init_lex();
		//shell->tok = init_tok();
		shell->cmds = init_cmds();
		shell->prompt = PROMPT;
		shell->env = envp;
	}
	return (shell);
}
