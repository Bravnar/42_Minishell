#include "minishell.h"

void	handle_redir_type(t_llex *tmp, t_type type, t_type type_next)
{
	tmp->type = type;
	if (tmp->next)
	{
		tmp = tmp->next;
		tmp->type = type_next;
		while (tmp->next && tmp->next->conn_with_prev)
		{
			tmp = tmp->next;
			tmp->type = type_next;
		}
	}
}

void	handle_redirs(t_llex *tmp)
{
	if (!ft_strcmp("<", tmp->value))
		handle_redir_type(tmp, REDIR_IN, INFILE);
	else if (!ft_strcmp(">", tmp->value))
		handle_redir_type(tmp, REDIR_OUT, OUTFILE);
	else if (!ft_strcmp("<<", tmp->value))
		handle_redir_type(tmp, HEREDOC, HEREDOC_END);
	else if (!ft_strcmp(">>", tmp->value))
		handle_redir_type(tmp, APPEND, OUTFILE_APP);
}
