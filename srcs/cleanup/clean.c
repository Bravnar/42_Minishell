#include "minishell.h"

void	free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->input)
		free(lex->input);
	if (lex->trim)
		free(lex->trim);
	if (lex->link)
		free_tokens(lex->link);
	if (lex)
		free(lex);
}

void	free_cmds(t_cmds *cmds)
{
	if (!cmds)
		return ;
	free(cmds);
}

void	free_count(t_counts *counts)
{
	if (!counts)
		return ;
	free(counts);
}


void	free_main(t_main *shell)
{
	if (!shell)
		return ;
	free_lex(shell->l);
	free_cmds(shell->cmds);
	free_count(shell->counts);
	free_nodes(shell->env);
	clear_t_cmds(shell);
	free (shell);
}
