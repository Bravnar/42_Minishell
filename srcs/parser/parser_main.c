#include "minishell.h"

/* void	parser_create_cmd_table(t_main *shell)
{
	t_llex	*tmp;
	t_cmds	*cmds_tmp;
	int		cmd_count;

	cmd_count = 0;
	cmds_tmp = shell->cmds;
	tmp = shell->l->link;
	while (tmp)
	{
		cmd_count = 0;
		while (tmp->next && tmp->type != PIPE_SYMBOL)
		{
			if (tmp->type == CMD)
				cmd_count++;
			add_cmd_to_table(cmds_tmp, cmd_count);
		}
	}
} */

void	parser_main(t_main *shell)
{
	t_lex	*lex;

	lex = shell->l;
	parser_logic(lex);  // <--- Sets the types within llex
	//parser_create_cmd_table();

}
