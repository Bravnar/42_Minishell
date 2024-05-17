#include "minishell.h"

void	free_files(t_files *files_list)
{
	t_files	*tmp;

	if (!files_list)
		return ;
	while (files_list)
	{
		tmp = files_list;
		files_list = files_list->next;
		free(tmp->file_name);
		free(tmp);
	}
}

t_files	*new_file(t_llex *llex, t_main *shell)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		return (NULL);
	if (llex->needs_exp)
		new->file_name = ft_strdup(get_env(&shell->env, llex->value));
	else
		new->file_name = ft_strdup(llex->value);
	new->type = llex->type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_file(t_files **file_head, t_files *new_file)
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

t_files	*get_files(t_llex **head, t_main *shell)
{
	t_llex	*tmp;
	t_files	*files_head;

	files_head = NULL;
	tmp = *head;
	while (tmp && tmp->type != PIPE_SYMBOL)
	{
		if (tmp && (tmp->type == INFILE || tmp->type == HEREDOC_END \
		|| tmp->type == OUTFILE || tmp->type == OUTFILE_APP))
			add_file(&files_head, new_file(tmp, shell));
		tmp = tmp->next;
	}
	if (tmp && tmp->next)
		tmp = tmp->next;
	*head = tmp;
	return (files_head);
}
