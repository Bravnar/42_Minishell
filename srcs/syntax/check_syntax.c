#include "minishell.h"

void	reset_quotes(t_lex *l)
{
	l->d_count = 0;
	l->d_quotes = 0;
	l->s_count = 0;
	l->s_quotes = 0;
	l->i = 0;

}

int	check_redirs(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	l->err_code = 0;
	while (tmp)
	{
		if (ft_strchr(REDIRS, tmp->value[0]))
		{
			if (ms_lstsize(l->link) == 1)
				l->err_code = BAD_REDIRS_NL;
			else if (tmp->next && ft_strchr(REDIRS, tmp->next->value[0]))
				l->err_code = BAD_REDIRS;
			else if (ft_strlen(tmp->value) > 2)
				l->err_code = BAD_REDIRS;
			else if (!tmp->next)
				l->err_code = BAD_REDIRS;
		}
		tmp = tmp->next;
	}
	if (l->err_code)
		return (1);
	return (0);
}

int	check_pipes(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	l->err_code = 0;
	while (tmp)
	{
		if (ft_strchr(PIPE, tmp->value[0]))
		{
			if (ms_lstsize(l->link) == 1)
				l->err_code = BAD_PIPES;
			else if (tmp->next && ft_strchr(PIPE, tmp->next->value[0]))
				l->err_code = BAD_PIPES;
			else if (ft_strlen(tmp->value) > 1)
				l->err_code = BAD_PIPES;
			else if (!tmp->next)
				l->err_code = BAD_PIPES;
		}
		tmp = tmp->next;
	}
	if (l->err_code)
		return (1);
	return (0);
}

int	check_quotes(t_lex *l)
{
	l->i = -1;
	while (l->trim[++l->i])
	{
		if (l->trim[l->i] == '\'' && !l->d_quotes)
		{
			l->s_quotes = !l->s_quotes;
			l->s_count++;
		}
		else if (l->trim[l->i] == '\"' && !l->s_quotes)
		{
			l->d_quotes = !l->d_quotes;
			l->d_count++;
		}
	}
	if (l->s_count % 2 || l->d_count % 2)
	{
		l->err_code = BAD_QUOTES;
		return (1);
	}
	return (0);
}


/* void	check_syntax(t_lex *l)
{
	t_llex *current;
	t_llex *prev;

	current = l->link;
	prev = NULL;
	while (current)
	{
		if (current->value && ft_strchr(SPECIAL, current->value[0]))
			l->err_code = check_special(current->value);
		if (current->value && ft_strchr(QUOTES, current->value[0]))
			l->err_code = check_quotes(current->value);
	}
} */
