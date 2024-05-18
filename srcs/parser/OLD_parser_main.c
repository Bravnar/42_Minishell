#include "minishell.h"

/* Should the files be a linked list too?
	perhaps it's better
	Explore option with linked list for files
	Have a struct that will store all counts
	Use ft_bzero to reset them
	 
	Steps:
	1) Create linked list inside of t_main shell that will contain files
	2) Store them with their type (?)
	3) Go over lex linked list until pipe
		a) Count every CMD type and create char **, add to t_cmds
		b) Go to top, count every FILE_IN, FILE_OUT, HEREDOC and APPEND
			Add them all with info such as index, in/out/append to their
			linked list and add to the t_cmds node
		c) complete the t_cmds with any other info
	CAREFUL, get_env for ARGS that need expansion
	4) Repeat until the end
	 */

void	print_files(t_files	**files)
{
	t_files	*tmp;

	tmp = *files;
	while (tmp)
	{
		printf("V:%s | TYPE: %d)-->\n", tmp->file_name, tmp->type);
		tmp = tmp->next;
	}
	printf(" NULL\n");
}

void	print_cmds_struct(t_cmds **cmds)
{
	t_cmds	*tmp;
	//int		i;

	tmp = *cmds;
	while (tmp)
	{
		//i = 1;
		printf("CMDS **: [\n");
		// while (tmp->cmd_grp[i])
		// 	printf("\"%s, \"", tmp->cmd_grp[i++]);
		// printf("cmd grp: %s\n", tmp->cmd_grp[1]);
		// printf("]\n");
		print_files(&tmp->files);
		printf("file_in: %s\n", tmp->file_in);
		printf("is_heredoc: %d\n", tmp->is_heredoc);
		printf("file_out: %s\n", tmp->file_out);
		printf("is_append: %d\n", tmp->is_append);
		tmp = tmp->next;
	}
}

void	count_all(t_counts *count, t_lex *lex)
{
	t_llex	*tmp;

	tmp = lex->link;
	while (tmp && tmp->type != PIPE_SYMBOL)
	{
		if (tmp->type == INFILE)
			count->count_in_files++;
		else if (tmp->type == OUTFILE)
			count->count_out_files++;
		else if (tmp->type == CMD)
			count->count_cmds++;
		tmp = tmp->next;
	}
}

void	get_last_infile(t_cmds *node, t_files *files)
{
	t_files	*tmp;

	tmp = files;
	if (!node || !files)
		return ;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			if (node->file_in)
				free(node->file_in);
			node->file_in = ft_strdup(tmp->file_name);
			node->is_heredoc = 0;
		}
		else if (tmp->type == HEREDOC)
		{
			if (node->file_in)
				free(node->file_in);
			node->file_in = ft_strdup(tmp->file_name);
			node->is_heredoc = 1;
		}
		tmp = tmp->next;
	}
}

void	get_last_outfile(t_cmds *node, t_files *files)
{
	t_files	*tmp;

	tmp = files;
	if (!node || !files)
		return ;
	while (tmp)
	{
		if (tmp->type == OUTFILE)
		{
			if (node->file_out)
				free(node->file_out);
			node->file_out = ft_strdup(tmp->file_name);
			node->is_append = 0;
		}
		else if (tmp->type == OUTFILE_APP)
		{
			if (node->file_out)
				free(node->file_out);
			node->file_out = ft_strdup(tmp->file_name);
			node->is_append = 1;
		}
		tmp = tmp->next;
	}
}

t_cmds	*new_cmds_node(char **cmds, t_files *files, int index)
{
	t_cmds	*node;

	// node = ft_calloc(1, sizeof(t_cmds));
	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->cmd_grp = cmds;
	node->files = files;
	node->index = index;
	get_last_infile(node, files);
	get_last_outfile(node, files);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_cmds_tbl(t_cmds **head, t_cmds *new_node)
{
	t_cmds	*tmp;

	if (!*head)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

char	**get_cmds(t_llex *tmp, t_main *shell)
{
	char	**cmd_list;
	int		i;

	i = 0;
	printf("count: %d\n", shell->counts->count_cmds);
	cmd_list = malloc(sizeof(char *) * (shell->counts->count_cmds + 1));
	if (!cmd_list)
		return (NULL);
	while (tmp && tmp->type != PIPE_SYMBOL)
	{
		if (tmp && tmp->type == CMD)
		{
			if (tmp->needs_exp)
				cmd_list[i++] = ft_strdup(get_env(&shell->env, tmp->value));
			else
				cmd_list[i++] = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}


void	parser_create_cmds(t_main *shell)
{
	t_counts	*count;
	t_llex		*tmp;
	t_files		*files_head;
	char		**cmds;

	count = shell->counts;
	tmp = shell->l->link;
	while (tmp)
	{
		cmds = NULL;
		files_head = NULL;
		if (tmp && tmp->type != PIPE_SYMBOL)
		{
			count_all(count, shell->l);
			cmds = get_cmds(tmp, shell);
			// if (!cmds)
			// 	continue ;
			files_head = get_files(&tmp, shell);
			//print_files(&files_head);
			// if (!files_head)
			// 	continue ;
			add_cmds_tbl(&shell->cmds, new_cmds_node(cmds, files_head, 0));
			ft_free_arr(cmds);
			cmds = NULL;
			free_files(files_head);
			files_head = NULL;
		}
		ft_bzero(count, sizeof(t_counts));
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}


/* void	parser_main(t_main *shell)
{
	t_lex	*lex;

	lex = shell->l;
	parser_logic(lex);
	parser_create_cmds(shell);
	// printf("Checking if shell->cmds is NULL: %p\n", (void*)shell->cmds);
	// if (shell->cmds != NULL && shell->cmds->cmd_grp != NULL)
    // 	printf("test: %s\n", shell->cmds->cmd_grp[0]);
	// else
    // 	printf("cmd_grp is NULL or shell->cmds is NULL\n");

	//print_cmds_struct(&shell->cmds);
} */

