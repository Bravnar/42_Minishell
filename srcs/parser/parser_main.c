#include "minishell.h"

void	print_main_struct(t_cmds **main)
{
	t_cmds	*tmp;
	int	i;

	tmp = *main;
	while (tmp)
	{
		i = -1;
		printf("Commands: \n");
		while (tmp->cmd_grp[++i])
			printf("[%s]\n", tmp->cmd_grp[i]);
		printf("Files: \n");
		while(tmp->files)
		{
			printf("name: %s type: %d\n", tmp->files->file_name, tmp->files->type);
			tmp->files = tmp->files->next;
		}
		printf("--------------------------\n");
		tmp = tmp->next;
	}
}

void	parser_body(t_main *shell)
{
	t_llex	*iter;
	t_files	*files;
	char	**cmds;
	int		count;

	iter = shell->l->link;
	while (iter)
	{
		count = 0;
		cmds = NULL;
		files = NULL;
		if (iter && iter->type != PIPE_SYMBOL)
		{
			count = count_commands(iter);
			cmds = create_cmd_arr(iter, shell, count);
			files = create_files_list(&iter, shell);
			add_cmds_node(&shell->cmds, new_cmds_node(cmds, files, 0));
			ft_free_arr(cmds);
			//free_files_nodes(files);
		}
		if (iter && iter->next)
			iter = iter->next;
	}
}

void	parser_main(t_main *shell)
{
	t_lex	*lex;
	
	lex = shell->l;
	parser_logic(lex);
	parser_body(shell);
	print_list(&lex->link);
	print_main_struct(&shell->cmds);
	clear_t_cmds(shell);
}
