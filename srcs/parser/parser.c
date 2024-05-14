#include "minishell.h"

void	parser(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	while (tmp)
	{
		if (tmp->next && tmp->next->type == 0 && tmp->type == 0)
		{
			if (!ft_strcmp("<", tmp->value))
			{
				tmp->type = REDIR_IN;
				tmp->next->type = INFILE;
			}
			else if (!ft_strcmp(">", tmp->value))
			{
				tmp->type = REDIR_OUT;
				tmp->next->type = OUTFILE;
			}
			else if (!ft_strcmp("<<", tmp->value))
			{
				tmp->type = HEREDOC;
				tmp->next->type = HEREDOC_END;
			}
			else if (!ft_strcmp(">>", tmp->value))
			{
				tmp->type = APPEND;
				tmp->next->type = OUTFILE;
			}
			else if (!ft_strcmp("|", tmp->value))
			{
				tmp->type = PIPE_SYMBOL;
				tmp = tmp->next;
				continue ;
			}
			else
				tmp->type = CMD;
		}
		else if (tmp->type == 0)
			tmp->type = CMD;
		tmp = tmp->next;
	}
}


