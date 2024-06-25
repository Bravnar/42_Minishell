/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:10:55 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/25 17:10:55 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files_nodes(t_files *head)
{
	t_files	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_cmds_nodes(t_cmds *head)
{
	t_cmds	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_files_nodes(tmp->files);
		if (tmp->cmd_grp && tmp->cmd_grp[0])
		{
			if (tmp->path)
				free(tmp->path);
			ft_free_arr(tmp->cmd_grp);
		}
		free(tmp);
	}
}

/* if (ft_strcmp(tmp->cmd_grp[0], "./minishell")) */

void	clear_t_cmds(t_main *shell)
{
	if (shell->cmds)
	{
		free_cmds_nodes(shell->cmds);
		shell->cmds = NULL;
	}
}
