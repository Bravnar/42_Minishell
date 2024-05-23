#include "minishell.h"

t_files	*new_file_node(t_llex *llex, t_main *shell)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		return (NULL);
	if (llex->needs_exp)
		new->file_name = ft_strdup(get_env(&shell->env, llex->value));
	else
		new->file_name = ft_strdup(llex->value);
	if (!new->file_name)
	{
		free(new);
		return (NULL);
	}
	new->type = llex->type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_file_node(t_files **file_head, t_files *new_file)
{
	t_files	*tmp;

	if (!*file_head)
		*file_head = new_file;
	else
	{
		tmp = *file_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_file;
		new_file->prev = tmp;
	}
}

t_files	*create_files_list(t_llex **tmp, t_main *shell)
{
	t_llex	*iter;
	t_files	*files_head;

	files_head = NULL;
	iter = *tmp;
	while (iter && iter->type != PIPE_SYMBOL)
	{
		if (iter && (iter->type == INFILE || iter->type == HEREDOC_END \
		|| iter->type == OUTFILE || iter->type == OUTFILE_APP))
			add_file_node(&files_head, new_file_node(iter, shell));
		iter = iter->next;
	}
	/* if (iter && iter->next)
		iter = iter->next; */
	*tmp = iter;
	return (files_head);
}