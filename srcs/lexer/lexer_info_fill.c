#include "minishell.h"

void	overwrite_exp(t_llex *tmp)
{
	if (tmp->needs_exp)
	{
		if ((tmp->is_in_quotes && ft_strchr(CANCEL_EXP, tmp->value[2])) || \
		(ft_strchr(CANCEL_EXP, tmp->value[1])))
			tmp->needs_exp = 0;
	}
}

void	work_args(t_llex *tmp)
{
	int		i;
	char	*swap;

	i = -1;
	if (ft_strchr(QUOTES, tmp->value[0]))
		tmp->is_in_quotes = tmp->value[0];
	if (tmp->value[0] == '$')
		tmp->needs_exp = 1;
	else if (tmp->is_in_quotes)
	{
		while (tmp->value[++i] && ft_strchr(QUOTES, tmp->value[i]))
			;
		if (tmp->value[i - 1] == '\"' && tmp->value[i] == '$')
			tmp->needs_exp = 1;
	}
	overwrite_exp(tmp);
	swap = ft_strtrim(tmp->value, &tmp->is_in_quotes);
	free(tmp->value);
	tmp->value = swap;
}

void	fill_info(t_lex *l)
{
	t_llex	*tmp;
	int		index;

	tmp = l->link;
	index = 0;
	while (tmp)
	{
		work_args(tmp);
		tmp->index = index++;
		tmp = tmp->next;
	}
}
