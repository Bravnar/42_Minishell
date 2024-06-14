#include "minishell.h"

void	print_main_struct(t_cmds **main)
{
	t_cmds	*tmp;
	t_files	*file_tmp;
	int		i;

	tmp = *main;
	while (tmp)
	{
		i = -1;
		printf("Commands: \n");
		while (tmp->cmd_grp[++i])
			printf("[%s]\n", tmp->cmd_grp[i]);
		printf("..............\nFiles: \n");
		file_tmp = tmp->files;
		while (file_tmp)
		{
			printf("name: %s type: %d\n", file_tmp->file_name, file_tmp->type);
			file_tmp = file_tmp->next;
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
			add_cmds_node(&shell->cmds, new_cmds_node(cmds, files, 0, shell));
			ft_free_arr(cmds);
			cmds = NULL;
		}
		if (iter && iter->next)
			iter = iter->next;
	}
}

/* Main parser function that does the following:
   1) parser_logic() sets the types for all tokens
      this is used as the main navigation system
	  to determine the rest afterwards
   2) parser_body() is the Big Bertha
      using the information from 1) it creates the
	  main structure to be passed to execution
	  using pipes as the main separator it creates
	  sub groups by putting commands and arguments into
	  a char ** and files to check for redirection into
	  a linked list within the main linked list
	  the final deliverable looks like this

	typedef struct s_cmds
	{
		char			**cmd_grp; ---> char ** of all cmds and args per pipe partion
		t_files			*files; ---> linked list of all files per pipe partition
		char			*file_in; ---> currently inactive, purpose is to store the last infile
		char			*file_out; ---> currently inactive, purpose is to store the last outfile
		int				is_heredoc; ---> I don't remember if used, probably not yet
		int				is_append; ---> idem
		int				index; ---> unused, but can be implemented
		struct s_cmds	*next;
		struct s_cmds	*prev;
	}	t_cmds;*/

void	parser_main(t_main *shell)
{
	t_lex	*lex;

	lex = shell->l;
	parser_logic(lex);
	parser_combiner(shell);
	parser_body(shell);
	//print_list(&lex->link);
	//print_main_struct(&shell->cmds);
}

/* void	parser_combiner(t_main *shell)
{
	t_llex	*iter;
	t_llex	*prev;
	char	*combined;

	iter = shell->l->link;
	while (iter)
	{
		if (iter->needs_exp)
		{
			iter->exp_tmp = expand_if_needed(iter, shell);
			free(iter->value);
			iter->value = iter->exp_tmp;
		}
		if (iter->conn_with_prev && iter->prev && (iter->type == iter->prev->type))
		{
			prev = iter->prev;
			combined = ft_strjoin(prev->value, iter->value);
			free(prev->value);
			prev->value = combined;
			prev->next = iter->next;
			if (iter->next)
				iter->next->prev = prev;
			free(iter->value);
			free(iter);
			iter = prev->next;
		}
		else
		{
			iter = iter->next;
		}
	}
} */
