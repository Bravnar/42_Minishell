#include "minishell.h"

int	print_envp(t_envp **head, int fd)
{
	t_envp	*tmp;

	tmp = *head;
	//printf("{\n");
	set_env(head, "_", "/usr/bin/env", 1);
	while (tmp != NULL)
	{
		// printf(BOLD_YELLOW"\t\"%s\" : \"%s\"\n"RESET, tmp->key, tmp->value);
		if (tmp->printable && tmp->printable != 777)
			ft_fprintf(fd, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
	// printf("}\n");
}
