#include "minishell.h"

void handle_simple_redirs(t_llex *tmp) 
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
}

void handle_complex_redirs(t_llex *tmp) 
{
    if (!ft_strcmp("<<", tmp->value)) 
	{
        tmp->type = HEREDOC;
        tmp->next->type = HEREDOC_END;
    } 
	else if (!ft_strcmp(">>", tmp->value)) 
	{
        tmp->type = APPEND;
        tmp->next->type = OUTFILE;
    }
}

void	handle_pipe(t_llex **tmp)
{
	(*tmp)->type = PIPE_SYMBOL;
	*tmp = (*tmp)->next;
}

void	parser(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	while (tmp)
	{
		if (tmp->next && !tmp->next->type && !tmp->type)
		{
			if (!ft_strcmp("<", tmp->value) || !ft_strcmp(">", tmp->value))
				handle_simple_redirs(tmp);
			else if (!ft_strcmp("<<", tmp->value) || !ft_strcmp(">>", tmp->value))
				handle_complex_redirs(tmp);
			else if (!ft_strcmp("|", tmp->value))
			{
				handle_pipe(&tmp);
				continue;
			}
			else
				tmp->type = CMD;
		}
		else if (!tmp->type)
			tmp->type = CMD;
		tmp = tmp->next;
	}
}

// void	parser(t_lex *l)
// {
// 	t_llex	*tmp;

// 	tmp = l->link;
// 	while (tmp)
// 	{
// 		if (tmp->next && tmp->next->type == 0 && tmp->type == 0)
// 		{
// 			if (!ft_strcmp("<", tmp->value))
// 			{
// 				tmp->type = REDIR_IN;
// 				tmp->next->type = INFILE;
// 			}
// 			else if (!ft_strcmp(">", tmp->value))
// 			{
// 				tmp->type = REDIR_OUT;
// 				tmp->next->type = OUTFILE;
// 			}
// 			else if (!ft_strcmp("<<", tmp->value))
// 			{
// 				tmp->type = HEREDOC;
// 				tmp->next->type = HEREDOC_END;
// 			}
// 			else if (!ft_strcmp(">>", tmp->value))
// 			{
// 				tmp->type = APPEND;
// 				tmp->next->type = OUTFILE;
// 			}
// 			if (!ft_strcmp("|", tmp->value))
// 			{
// 				tmp->type = PIPE_SYMBOL;
// 				tmp = tmp->next;
// 				continue ;
// 			}
// 			else
// 				tmp->type = CMD;
// 		}
// 		else if (tmp->type == 0)
// 			tmp->type = CMD;
// 		tmp = tmp->next;
// 	}
// }


