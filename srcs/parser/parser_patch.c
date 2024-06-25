/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_patch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:00:23 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/25 17:00:23 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	patch_commands(char ***cmds)
{
	char	*space;
	char	*remaining;
	char	**subcoms;

	space = ft_strdup(ft_superstrchr((*cmds)[0], " \n\t"));
	if (space != NULL && space[0] != '\0')
	{
		remaining = ft_strdup(space + 1);
		subcoms = ft_split((*cmds)[0], space[0]);
		*cmds = strarr_pop(*cmds, 0);
		*cmds = arr_insert(*cmds, 0, remaining);
		*cmds = arr_insert(*cmds, 0, subcoms[0]);
		free(remaining);
		ft_free_arr(subcoms);
	}
	free(space);
}
