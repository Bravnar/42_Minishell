/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:20:29 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/25 07:41:38 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_underscore(t_cmds *cmds, t_main *shell)
{
	char	*underscore;
	int		i;

	if (cmd_size(cmds) > 1)
		return ;
	if (!cmds->cmd_grp)
	{
		underscore = "\0";
		set_env(&shell->env, "_", underscore, 1);
		return ;
	}
	else
	{
		i = -1;
		while (cmds->cmd_grp[++i])
			;
		underscore = ft_strdup(cmds->cmd_grp[i - 1]);
		set_env(&shell->env, "_", underscore, 1);
	}
	free(underscore);
}
