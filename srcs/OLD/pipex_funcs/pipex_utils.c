/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:06:59 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/02 13:15:02 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exec_path(char *cmd, char **env)
{
	int		i;
	char	**split_path;
	char	**split_cmd;
	char	*adj_path;
	char	*exec_path;

	i = -1;
	split_path = ft_split(get_path_line(env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (split_path[++i])
	{
		adj_path = ft_strjoin(split_path[i], "/");
		exec_path = ft_strjoin(adj_path, split_cmd[0]);
		free(adj_path);
		if (!access(exec_path, F_OK | X_OK))
		{
			free_arr(split_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	free_arr(split_path);
	free_arr(split_cmd);
	return (cmd);
}

void	exec(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = pipex_parse(cmd);
	path = get_exec_path(cmd_split[0], envp);
	if (execve(path, cmd_split, envp) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd_split[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		free_arr(cmd_split);
		exit(127);
	}
}

int	my_open(char *file, char type)
{
	int	fd;

	if (type == 'i')
		fd = open(file, O_RDONLY, 0644);
	if (type == 'o')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*get_path_line(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 4))
			return (envp[i] + 5);
	}
	return (NULL);
}
