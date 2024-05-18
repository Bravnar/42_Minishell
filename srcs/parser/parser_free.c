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
		ft_free_arr(tmp->cmd_grp);
		free(tmp->file_in);
		free(tmp->file_out);
		free(tmp);
	}
}

void	clear_t_cmds(t_main *shell)
{
	if (shell->cmds)
	{
		free_cmds_nodes(shell->cmds);
		shell->cmds = NULL;
	}
}