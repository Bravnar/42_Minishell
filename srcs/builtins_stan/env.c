/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:35:40 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 12:35:58 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_envp(t_envp **head, int fd)
{
	t_envp	*tmp;

	tmp = *head;
	set_env(head, "_", "/usr/bin/env", 1);
	while (tmp != NULL)
	{
		if (tmp->printable && tmp->printable != 777)
			ft_fprintf(fd, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/* printf("{\n"); */
/* printf(BOLD_YELLOW"\t\"%s\" : \"%s\"\n"RESET, tmp->key, tmp->value); */
/* printf("}\n"); */
