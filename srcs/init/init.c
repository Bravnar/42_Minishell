#include "minishell.h"

/* t_llex	*init_llex(void)
{
	return (calloc(1, sizeof(t_llex)));
} */

/* t_counts	*init_counts(void)
{
	return (ft_calloc(1, sizeof(t_counts)));
} */

t_lex	*init_lex(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	return (lex);
}

/* t_cmds	*init_cmds(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->files = init_files();
	cmds->cmd_grp = NULL;
	cmds->file_in = NULL;
	cmds->file_out = NULL;
	cmds->index = 0;
	cmds->is_append = 0;
	cmds->is_heredoc = 0;
	return (cmds);
} */

t_main	*init_structs(char **envp)
{
	t_main	*shell;

	shell = ft_calloc(1, sizeof(t_main));
	if (shell)
	{
		shell->l = init_lex();
		// shell->counts = init_counts();
		shell->envp = envp;
		shell->has_env = 1;
		populate_envp(shell);
		terminal_prompt(shell);
		shell->username = get_env(&shell->env, "$USER");
		if (shell->username == NULL)
			shell->prompt = BOLD_YELLOW FACE BOLD_WHITE THROW RESET;
	}
	return (shell);
}
