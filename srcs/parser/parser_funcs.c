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

void	handle_pipe(t_llex **tmp)
{
	(*tmp)->type = PIPE_SYMBOL;
	*tmp = (*tmp)->next;
}

void	parser_logic(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	while (tmp)
	{
		if (tmp->next && !tmp->next->type && !tmp->type)
		{
			if (!ft_strcmp("<", tmp->value) || !ft_strcmp(">", tmp->value) \
					|| !ft_strcmp("<<", tmp->value) || \
				 	!ft_strcmp(">>", tmp->value))
				handle_redirs(tmp);
			else if (!ft_strcmp("|", tmp->value))
			{
				handle_pipe(&tmp);
				continue ;
			}
			else
				tmp->type = CMD;
		}
		else if (!tmp->type)
			tmp->type = CMD;
		tmp = tmp->next;
	}
}

/* void	handle_complex_redirs(t_llex *tmp)
{
	if (!ft_strcmp("<<", tmp->value))
	{
		tmp->type = HEREDOC;
		tmp->next->type = HEREDOC_END;
	}
	else if (!ft_strcmp(">>", tmp->value))
	{
		tmp->type = APPEND;
		tmp->next->type = OUTFILE_APP;
	}
} */

/* void	handle_simple_redirs(t_llex *tmp)
{
	if (!ft_strcmp("<", tmp->value))
	{
		tmp->type = REDIR_IN;
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = INFILE;
			while (tmp->next && tmp->next->conn_with_prev)
			{
				tmp = tmp->next;
				tmp->type = INFILE;
			}
		}
	}
	else if (!ft_strcmp(">", tmp->value))
	{
		tmp->type = REDIR_OUT;
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = OUTFILE;
			while (tmp->next && tmp->next->conn_with_prev)
			{
				tmp = tmp->next;
				tmp->type = OUTFILE;
			}
		}
	}
}

void	handle_complex_redirs(t_llex *tmp)
{
	if (!ft_strcmp("<<", tmp->value))
	{
		tmp->type = HEREDOC;
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = HEREDOC_END;
			while (tmp->next && tmp->next->conn_with_prev)
			{
				tmp = tmp->next;
				tmp->type = HEREDOC_END;
			}
		}
	}
	else if (!ft_strcmp(">>", tmp->value))
	{
		tmp->type = APPEND;
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = OUTFILE_APP;
			while (tmp->next && tmp->next->conn_with_prev)
			{
				tmp = tmp->next;
				tmp->type = OUTFILE_APP;
			}
		}
	}
} */