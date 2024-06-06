#include "minishell.h"

char	**get_paths(t_main *shell)
{
	char	**paths;
	char	*path;

	path = get_env(&shell->env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_path(char **paths, char *command)
{
	char	*path;
	char	*subcommand;

	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	subcommand = ft_strjoin("/", command);
	while (*paths)
	{
		path = ft_strjoin(*paths, subcommand);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		paths++;
	}
	free(subcommand);
	if (access(path, F_OK) == 0)
		return (path);
	return (NULL);
}