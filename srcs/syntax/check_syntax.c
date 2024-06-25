
#include "minishell.h"

void	set_redir_err(t_lex *l, t_llex *tmp)
{
	int	lst_size;

	lst_size = ms_lstsize(l->link);
	if (lst_size == 1)
		l->err_code = set_err_code("\n");
	else if (is_last(tmp))
		l->err_code = set_err_code("\n");
	else if (ft_strlen(tmp->value) > 2)
		l->err_code = set_err_code(tmp->value);
	else if (!is_last(tmp) && ft_strchr(REDIRS, tmp->next->value[0]))
		l->err_code = set_err_code(tmp->next->value);
	else if (!is_last(tmp) && ft_strchr(PIPE, tmp->next->value[0]))
		l->err_code = set_err_code("|");
}

int	check_redirs(t_lex *l)
{
	t_llex	*tmp;

	tmp = l->link;
	l->err_code = 0;
	while (tmp)
	{
		if (tmp->value[0] != '\0' && ft_strchr(REDIRS, tmp->value[0]))
			set_redir_err(l, tmp);
		tmp = tmp->next;
	}
	if (l->err_code)
		return (1);
	return (0);
}

int	check_spec(t_lex *l)
{
	t_llex	*tmp;
	int		i;
	int		stop;

	stop = 0;
	tmp = l->link;
	l->err_code = 0;
	while (tmp && !stop)
	{
		i = 0;
		while (tmp->value[i] && !tmp->is_in_quotes)
		{
			if (tmp->value[0] != '\0' && ft_strchr(SYNTAX_STOP, tmp->value[i]))
			{
				l->err_code = FORB_CHAR;
				stop = 1;
				break ;
			}
			i++;
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
		if (tmp->value[0] != '\0' && ft_strchr(PIPE, tmp->value[0]))
		{
			if (ms_lstsize(l->link) == 1)
				l->err_code = BAD_PIPES;
			else if (is_first(tmp) || is_last(tmp))
				l->err_code = BAD_PIPES;
			else if (tmp->next && ft_strchr(PIPE, tmp->next->value[0]))
				l->err_code = BAD_PIPES;
			else if (ft_strlen(tmp->value) > 1)
				l->err_code = BAD_PIPES;
			else if (!tmp->next)
				l->err_code = BAD_REDIRS_NL;
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
