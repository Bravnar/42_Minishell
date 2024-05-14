#include "minishell.h"

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
