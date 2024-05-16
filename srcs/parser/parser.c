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

void	parser_logic(t_lex *l)
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

/* t_cmds	*lex_to_cmds(t_main *shell, t_lex *lex)
{
	t_llex	*tmp;

	tmp = lex->link;
	while (tmp)
	{
		while (tmp && tmp->type != PIPE_SYMBOL)
		{
			if (tmp->type == CMD)
				add_to_arr();
			else if (tmp->type == INFILE || tmp->type == OUTFILE)
				assign_file();
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
} */

void	parser_main(t_lex *lex)
{
	//t_lex	*lex;
	//t_cmds	*new_node;

	//lex = shell->l;
	parser_logic(lex);
	//shell->cmds = lex_to_cmds(shell, lex);

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


/* How to do:
	go over the linked list
	if you encounter redir_in or redir_out or heredoc or append
	save into file_in / file_out until meet pipe (overwriting the stuff)
	then delete each one of these nodes
	the goal is to remain with only cmds and args
	malloc an char ** of size of linked list up until the pipe (maybe counter variable)
	then skip pipe,
	rinse and repeat until end of linked list
 */