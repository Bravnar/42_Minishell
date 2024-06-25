/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 24/06/2024 10:38:18 by smuravye          #+#    #+#             */
/*   Updated: 24/06/2024 10:38:49 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_local_copy(t_envp *local)
{
	t_envp	*tmp;

	if (!local)
		return ;
	while (local)
	{
		tmp = local;
		local = local->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	tmp = NULL;
}

int	count_export_args(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

void	print_local_copy(t_envp **head, int fd)
{
	t_envp	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->printable != 777)
		{
			if (!(tmp->key && tmp->key[0] == '_' && !tmp->key[1]))
			{
				if (!tmp->value)
					ft_fprintf(fd, "declare -x %s\n", tmp->key);
				else
					ft_fprintf(fd, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			}
		}
		tmp = tmp->next;
	}
}

void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr)
{
	n_n->key = ft_strdup(curr->key);
	n_n->value = ft_strdup(curr->value);
	n_n->printable = curr->printable;
	n_n->next = NULL;
	n_n->prev = *l_t;
	if (*l_t)
		(*l_t)->next = n_n;
	else
		*l_h = n_n;
	*l_t = n_n;
}
