#include "minishell.h"

char	*expand_if_needed(t_llex *iter, t_main *shell)
{
	char	*result;
	t_llex	*tmp;

	result = NULL;
	tmp = iter;
	printf("I entered expand if needed, with %s\n", iter->value);
	if (tmp->type == HEREDOC_END)
		return (ft_strdup(tmp->value));
	if (tmp->is_in_quotes == 34)
		result = var_replace(tmp->value, shell);
	else if (!tmp->is_in_quotes)
	{
		printf("I enter here to get_env\n");
		result = ft_strdup(get_env(&shell->env, tmp->value));
	}
	else
		return (result);
	return (result);
}

void	expand_and_replace(t_llex *iter, t_main *shell)
{
	if (iter->needs_exp)
	{
		iter->exp_tmp = expand_if_needed(iter, shell);
		free(iter->value);
		iter->value = iter->exp_tmp;
	}
}

void	combine_with_prev(t_llex *iter)
{
	t_llex	*prev;
	char	*combined;

	prev = iter->prev;
	combined = ft_strjoin(prev->value, iter->value);
	free(prev->value);
	prev->value = combined;
	prev->next = iter->next;
	if (iter->next)
		iter->next->prev = prev;
	free(iter->value);
	free(iter);
}

void	parser_combiner(t_main *shell)
{
	t_llex	*iter;
	t_llex	*next_iter;

	iter = shell->l->link;
	while (iter)
	{
		expand_and_replace(iter, shell);
		if (iter->conn_with_prev && \
			iter->prev && (iter->type == iter->prev->type))
		{
			next_iter = iter->next;
			combine_with_prev(iter);
			iter = next_iter;
		}
		else
			iter = iter->next;
	}
}
