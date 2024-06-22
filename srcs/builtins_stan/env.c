#include "minishell.h"

void	print_envp(t_envp **head)
{
	t_envp	*tmp;

	tmp = *head;

	//printf("{\n");
	set_env(head, "_", "/usr/bin/env", 1);
	while (tmp != NULL)
	{
		// printf(BOLD_YELLOW"\t\"%s\" : \"%s\"\n"RESET, tmp->key, tmp->value);
		if (tmp->printable && tmp->printable != 777)
			printf("%s=%s ---> printable: %d\n", tmp->key, tmp->value, tmp->printable);
		tmp = tmp->next;
	}
	// printf("}\n");
}
