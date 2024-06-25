/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 23/06/2024 13:00:06 by hmorand           #+#    #+#             */
/*   Updated: 24/06/2024 10:48:23 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_main *shell)
{
	char	**paths;
	char	*path;

	path = get_env(&shell->env, "PATH");
	if (!path || !path[0])
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/* This function causes issues when the thing passed to it is not a command
   Valgrind is unhappy because it tries access something that is not  */
char	*get_path(char **paths, char *command)
{
	char	*path;
	char	*subcommand;

	if (!command)
		return (NULL);
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	if (!paths)
		return (NULL);
	subcommand = ft_strjoin("/", command);
	while (*paths)
	{
		path = ft_strjoin(*paths, subcommand);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		paths++;
	}
	free(subcommand);
	if (path)
		return (path);
	return (NULL);
}
