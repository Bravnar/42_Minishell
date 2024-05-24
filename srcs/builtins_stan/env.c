#include "minishell.h"

void	print_envp(t_envp **head)
{
	t_envp	*tmp;

	tmp = *head;

	//printf("{\n");
	set_env(head, "_", "/usr/bin/env");
	while (tmp != NULL)
	{
		// printf(BOLD_YELLOW"\t\"%s\" : \"%s\"\n"RESET, tmp->key, tmp->value);
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	// printf("}\n");
}
