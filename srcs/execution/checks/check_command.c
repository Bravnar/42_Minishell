/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:10:52 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 09:10:52 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bad_command(t_cmds *cmds, t_main *shell)
{
	int	fd;
	DIR	*dir;

	if (!cmds->path)
		shell->err_code = NO_COMMAND;
	if (!cmds->path)
		return (127);
	fd = open(cmds->path, O_RDONLY, 00644);
	dir = opendir(cmds->path);
	if (fd == -1)
	{
		if (access(cmds->path, F_OK) == 0)
		{
			if (access(cmds->path, F_OK) == 0)
				shell->err_code = PERM_DENIED;
		}
	}
	else if (dir)
	{
		shell->err_code = IS_DIR;
		closedir(dir);
		return (126);
	}
	close (fd);
	return (EXIT_SUCCESS);
}
