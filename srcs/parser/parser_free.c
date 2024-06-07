#include "minishell.h"

void	free_files_nodes(t_files *head)
{
	t_files	*tmp;

	// printf("Entering free_files_nodes\n");
	while (head)
	{
		tmp = head;
		head = head->next;
		// printf("Freeing file_name: %s\n", tmp->file_name);
		free(tmp->file_name);
		free(tmp);
	}
	// printf("Exiting free_files_nodes\n");
}

void	free_cmds_nodes(t_cmds *head)
{
	t_cmds	*tmp;

	// printf("Entering free_cmds_nodes\n");
	while (head)
	{
		tmp = head;
		head = head->next;
		// printf("Freeing files linked list\n");
		free_files_nodes(tmp->files);
		// printf("Freeing cmd_grp array\n");
		if (ft_strcmp(tmp->cmd_grp[0], "./minishell"))
			free(tmp->path);
		ft_free_arr(tmp->cmd_grp);
		free(tmp);
	}
	// printf("Exiting free_cmds_nodes\n");
}

void	clear_t_cmds(t_main *shell)
{
	if (shell->cmds)
	{
		free_cmds_nodes(shell->cmds);
		shell->cmds = NULL;
	}
}
