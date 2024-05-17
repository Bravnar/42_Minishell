#include "minishell.h"

/* t_llex	*init_llex(void)
{
	return (calloc(1, sizeof(t_llex)));
} */

t_counts	*init_counts(void)
{
	return (ft_calloc(1, sizeof(t_counts)));
}

t_lex	*init_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	return (lex);
}

t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	return (cmds);
}

t_main	*init_structs(char **envp)
{
	t_main	*shell;

	shell = ft_calloc(1, sizeof(t_main));
	if (shell)
	{
		shell->l = init_lex();
		shell->cmds = init_cmds();
		shell->counts = init_counts();
		shell->prompt = PROMPT;
		shell->envp = envp;
		populate_envp(shell);
	}
	return (shell);
}
