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

/* Function to populate the no environment linked list (hardcoded) */
void	populate_no_env(t_main *shell)
{
	t_envp	*new_node;
	char	*get_path;

	get_path = my_get_path();
	new_node = new_env_node("PWD", get_path);
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("SHLVL", "1");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("_", "/usr/bin/env");
	add_env_node(&shell->env, new_node);
	new_node = new_env_node("HOME", NULL);
	add_env_node(&shell->env, new_node);
	free(get_path);
}

/* Function to create the prompt for the no environment program */
void	make_no_env_prompt(t_main *shell)
{
	char	*cwd;
	char	*first_part;
	char	*second_part;
	char	*final;

	if (shell->prompt)
		free(shell->prompt);
	cwd = my_get_path();
	first_part = ft_better_join(FACE, THROW);
	second_part = ft_better_join(first_part, cwd);
	final = ft_better_join(second_part, X_YELLOW);
	shell->prompt = ft_strdup(final);
	free(cwd);
	free(first_part);
	free(second_part);
	free(final);
}

/* Main no_env function */
void	no_env_handle(t_main *shell)
{
	shell->has_env = 0;
	shell->prompt = NULL;
	populate_no_env(shell);
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

/* CAREFUL THIS LEAKS */

char	*handle_quote(t_envp **head, char *var)
{
	char	*trim;
	char	*expand;
	char	*first;
	char	*result;

	trim = ft_strtrim(var, "'");
	expand = get_env(head, trim);
	free(trim);
	first = ft_better_join("'", expand);
	result = ft_better_join(first, "'");
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
	{
		no_env_handle(shell);
		return ;
	}
	i = -1;
	while (shell->envp[++i])
	{
		tmp_split = ft_split(shell->envp[i], '=');
		if (!ft_strcmp(tmp_split[0], "SHLVL"))
		{
			printf("populating SHLVL\n");
			tmp_num = ft_atoi(tmp_split[1]);
			printf("tmp_num before ++: %d\n", tmp_num);
			tmp_num++;
			printf("tmp_num after ++: %d\n", tmp_num);
			free(tmp_split[1]);
			tmp_split[1] = ft_itoa(tmp_num);
			printf("tmp_split = %s\n", tmp_split[1]);
		}
		new_node = new_env_node(tmp_split[0], tmp_split[1]);
		add_env_node(&shell->env, new_node);
		ft_free_arr(tmp_split);
	}
}
