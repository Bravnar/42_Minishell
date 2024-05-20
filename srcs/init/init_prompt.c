#include "minishell.h"

void	terminal_prompt(t_main *shell)
{
	char	*username;
	char	*hostname;
	char	*curr_wd;
	char	*part;
	char	*full;

	if (!shell->has_env)
		return ;
	if (shell->prompt != NULL)
		free(shell->prompt);
	username = ft_strdup(get_env(shell->env, "USER"));
	hostname = ft_strdup("@Ecole42 :");
	curr_wd = ft_strdup(get_env(shell->env, "PWD"));
	part = ft_strjoin(username, hostname);
	full = ft_strjoin(part, curr_wd);
	
}