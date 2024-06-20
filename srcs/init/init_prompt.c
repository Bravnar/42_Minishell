#include "minishell.h"

char	*create_home(char **part)
{
	char	*result;
	char	*tmp;

	if (!part)
		return (NULL);
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

	home = create_home(part);
	if (!part || !part[0] || !home)
		return (ft_strdup("/"));
	i = 0;
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
		result = ft_better_join(tmp, part[i++], 0);
		free (tmp);
	}
	return (result);
}

void	terminal_prompt_nonroot(t_main *shell, char **path)
{
	char	**breakdown;
	char	*tmp;
	char	*full_start;
	char	*end;
	char	*final;


	breakdown = NULL;
	breakdown = ft_split(*path, '/');
	free(*path);
	tmp = ft_better_join(G_ARROW_SIGN, MINISH, 0);
	full_start = ft_better_join(tmp, EHL, 0);
	free(tmp);
	tmp = join_prompt(breakdown, shell);
	ft_free_arr(breakdown);
	end = ft_better_join(tmp, X_SIGN, 0);
	final = ft_better_join(full_start, end, 0);

	shell->prompt = ft_strdup(final);
	free(tmp);
	free(full_start);
	free(end);
	free(final);
}

void	terminal_prompt_root(t_main *shell, char **path)
{
	char	*tmp;
	char	*full_start;
	char	*end;
	char	*final;

	free(*path);
	tmp = ft_better_join(G_ARROW_SIGN, MINISH, 0);
	full_start = ft_better_join(tmp, EHL, 0);
	free(tmp);
	tmp = join_prompt(NULL, shell);
	end = ft_better_join(tmp, X_SIGN, 0);
	final = ft_better_join(full_start, end, 0);
	shell->prompt = ft_strdup(final);
	free(tmp);
	free(full_start);
	free(end);
	free(final);
}

void	terminal_prompt(t_main *shell)
{
	char	*path;

	if (!shell->has_env)
	{
		make_no_env_prompt(shell);
		return ;
	}
	if (shell->prompt)
		free(shell->prompt);
	path = my_get_path();
	if (ft_strcmp(path, "/"))
		terminal_prompt_nonroot(shell, &path);
	else
		terminal_prompt_root(shell, &path);
}

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
