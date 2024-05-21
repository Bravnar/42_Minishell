#include "minishell.h"

char	*join_prompt(char **part)
{
	int		i;
	char	*result;
	char	*tmp;

	if (!part || !part[0])
		return (NULL);
	result = ft_strdup("");
	i = 1;
	while (part[++i])
	{
		tmp = ft_strjoin(result, "/");
		free(result);
		result = ft_strjoin(tmp, part[i]);
		free (tmp);
	}
	tmp = ft_strjoin("~", result);
	free(result);
	return (tmp);
}

void	terminal_prompt(t_main *shell)
{
	char	*intro;
	char	**curr_wd;
	char	*full;
	char	*tmp;
	char	*final;

	if (!shell->has_env)
		return ;
	if (shell->prompt != NULL)
		free(shell->prompt);
	intro = ft_strdup(SHELL);
	curr_wd = ft_split(get_env(&shell->env, "PWD"), '/');
	tmp = join_prompt(curr_wd);
	ft_free_arr(curr_wd);
	full = ft_strjoin(intro, tmp);
	final = ft_strjoin(full, "$ ");
	//full = ft_strjoin(full, "$ ");
	shell->prompt = ft_strdup(final);
	free(intro);
	free(final);
	free(full);
	free(tmp);
}
