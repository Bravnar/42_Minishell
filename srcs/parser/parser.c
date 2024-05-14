#include "minishell.h"

void	has_arg(t_tok *new_tok, t_llex *cur_lex)
{
	int	i;

	i = -1;
	if (cur_lex->value[0] == '$')
		new_tok->needs_expansion = 1;
	else if (new_tok->is_in_quotes)
	{
		while (cur_lex->value[++i] == '\'' || cur_lex->value[i] == '\"')
			;
		if (cur_lex->value[i - 1] == '\"' && cur_lex->value[i] == '$')
			new_tok->needs_expansion = 1;
	}
}

void	has_quotes(t_tok *new_tok, t_llex *cur_lex)
{
	if (ft_strchr(QUOTES, cur_lex->value[0]))
		new_tok->is_in_quotes = cur_lex->value[0];
}

void	parser(t_main *shell)
{
	t_llex	*cur_lex;
	t_tok	*head;
	t_tok	*new_tok;
	int		index;

	index = 0;
	cur_lex = shell->l->link;
	head = NULL;
	while (cur_lex)
	{
		new_tok = tok_new_token(cur_lex->value);
		has_quotes(new_tok, cur_lex);
		has_arg(new_tok, cur_lex);
		new_tok->index = index++;
		tok_add_token(&head, new_tok);
		cur_lex = cur_lex->next;
	}
	tok_print_list(&head);
	//def_type(&head);
}
