#include "minishell.h"

char	*create_home(char **part)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("/");
	tmp = NULL;
	if (part[0] && part[1])
	{
		tmp = ft_better_join(result, part[0], 0);
		free(result);
		result = ft_better_join(tmp, "/", 0);
		free(tmp);
		tmp = ft_better_join(result, part[1], 0);
		free(result);
	}
	else if (part[0])
	{
		tmp = ft_better_join(result, part[0], 0);
		free(result);
	}
	else
		tmp = result;
	return (tmp);
}

char	*join_prompt(char **part, t_main *shell)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*home;

	// if (!part)
	// 	return (NULL);
	// if (!part[0])
	// 	return ft_strdup("/");
	if (!part || !part[0])
		return (ft_strdup("/"));
	i = 0;
	home = create_home(part);
	if (!home)
		return (ft_strdup("/"));
	if (!ft_strcmp(home, shell->home))
	{
		result = ft_strdup("~");
		i = 2;
	}
	else
		result = ft_strdup(home);
	free(home);
	while (i > 1 && part[i])
	{
		tmp = ft_better_join(result, "/", 0);
		free(result);
		result = ft_better_join(tmp, part[i], 0);
		free (tmp);
		i++;
	}
	return (result);
}


/* Refactor to reduce (26 lines!!)
   Function that creates the prompt 
   It uses a group of defined strings to
   strjoin them and output to the prompt */
void	terminal_prompt(t_main *shell)
{
	char	**cwd;
	char	*tmp;
	char	*full_start;
	char	*end;
	char	*final;
	char	*path;

	if (!shell->has_env)
		return ;
	if (shell->prompt)
		free(shell->prompt);
	path = my_get_path();
	cwd = ft_split(path, '/');
	free(path);
	tmp = ft_better_join(G_ARROW_SIGN, MINISH, 0);
	full_start = ft_better_join(tmp, EHL, 0);
	free(tmp);
	tmp = join_prompt(cwd, shell);
	ft_free_arr(cwd);
	end = ft_better_join(tmp, X_SIGN, 0);
	final = ft_better_join(full_start, end, 0);
	shell->prompt = ft_strdup(final);
	free(tmp);
	free(full_start);
	free(end);
	free(final);
}

/* char	*set_cwd_start(t_main *shell)
{
	char	*path_2;
	char	*path_3;
	char	*path_4;
	char	*result;

	if (shell->tmp_path)
		free(shell->tmp_path);
	shell->tmp_path = my_get_path();
	path_2 = ft_strchr(path + 1, '/');
	path_3 = ft_strchr(path_2 + 1, '/');
	path_4 = ft_strndup(path, path_2 - path);
	if (!ft_strcmp(shell->tmp_path, "/") || !ft_strcmp(shell->tmp_path, path_4))
		result = ft_strdup(shell->tmp_path);
	else
		result = ft_strdup("~");
	free(path);
	free(path_4);
	return (result);
}
char	*cwd_join(char *start, char *cwd)
{
	int	len;

	len = ft_strlen(shell->home);

}

char	*set_cwd(t_main *shell)
{
	char	*start_cwd;
	char	*final;
	//char	*cwd;

	start_cwd = NULL;
	start_cwd = set_cwd_start(shell);
	//cwd = my_get_path();
	if (!ft_strcmp(shell->tmp_path, shell->home))
		final = ft_strdup(start_cwd);
	else
		final = cwd_join(start_cwd, shell->tmp_path);
	free(start_cwd);
	//free(cwd);
	return (final);
}

void	terminal_prompt(t_main *shell)
{
	char	*cwd;
	char	*part_1;
	char	*part_2;
	char	*part_3;
	char	*final;

	cwd = set_cwd(shell);
	part_1 = ft_better_join(G_ARROW_SIGN, MINISH, 0);
	part_2 = ft_better_join(part_1, EHL, 0);
	part_3 = ft_better_join(part_2, cwd, 0);
	final = ft_better_join(part_3, X_SIGN, 0);
	shell->prompt = ft_strdup(final);
	free(cwd);
	free(part_1);
	free(part_2);
	free(part_3);
	free(final);
} */

/* Additional function to debug - not needed otherwise */
void print_prompt_info(const char *prompt) 
{
    int visible_length = 0;
    int actual_length = ft_strlen(prompt);
    int i = 0;

    while (prompt[i] != '\0') {
        if (prompt[i] == '\001') {
            while (prompt[i] != '\002' && prompt[i] != '\0') {
                i++;
            }
            if (prompt[i] == '\002') {
                i++;
            }
        } else {
            visible_length++;
            i++;
        }
    }

    printf("Prompt: %s\n", prompt);
    printf("Actual Length: %d\n", actual_length);
    printf("Visible Length: %d\n", visible_length);
}
