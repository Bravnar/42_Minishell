#include "minishell.h"

int	cmd_size(t_cmds *cmds)
{
	t_cmds	*tmp;
	int		len;

	tmp = cmds;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
