/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 22/06/2024 17:19:52 by smuravye          #+#    #+#             */
/*   Updated: 24/06/2024 11:00:50 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(int fd, t_main *shell, char **cmds)
{
	char	*pwd_to_print;
	int		cmds_count;

	cmds_count = count_export_args(cmds);
	pwd_to_print = my_get_path();
	ft_fprintf(fd, "%s\n", pwd_to_print);
	free(pwd_to_print);
	set_env(&shell->env, "_", cmds[cmds_count - 1], 1);
	return (EXIT_SUCCESS);
}
