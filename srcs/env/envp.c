/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 22/06/2024 17:19:52 by smuravye          #+#    #+#             */
/*   Updated: 24/06/2024 11:05:03 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adapted function to easily get current working directory */
char	*my_get_path(void)
{
	char	*get_path;
	char	path[1024];

	get_path = NULL;
	get_path = getcwd(get_path, sizeof(path));
	return (get_path);
}

/* Function that handles the '~' character during the main getter function */
char	*handle_tilde(t_envp **head, char *var)
{
	char	*home;
	char	*result;

	home = get_env(head, "HOME");
	var++;
	if (*var && *var == '/')
	{
		result = ft_strjoin(home, var);
		return (result);
	}
	return (home);
}

char	*handle_quote(t_envp **head, char *var)
{
	char	*trim;
	char	*expand;
	char	*first;
	char	*result;

	trim = ft_strtrim(var, "'");
	expand = get_env(head, trim);
	free(trim);
	first = ft_better_join("'", expand, 0);
	result = ft_better_join(first, "'", 0);
	free(first);
	return (result);
}

/* Function that is called once at the beginning of the
program to create our local copy of the envp */
void	populate_envp(t_main *shell)
{
	int		i;
	int		tmp_num;
	char	**tmp_split;
	t_envp	*new_node;

	if (shell->envp[0] == NULL)
		no_env_handle(shell);
	if (shell->envp[0] == NULL)
		return ;
	i = -1;
	while (shell->envp[++i])
	{
		tmp_split = ft_split(shell->envp[i], '=');
		if (!ft_strcmp(tmp_split[0], "SHLVL"))
		{
			tmp_num = ft_atoi(tmp_split[1]);
			tmp_num++;
			free(tmp_split[1]);
			tmp_split[1] = ft_itoa(tmp_num);
		}
		new_node = new_env_node(tmp_split[0], tmp_split[1]);
		add_env_node(&shell->env, new_node);
		ft_free_arr(tmp_split);
	}
	shell->envp = NULL;
}
