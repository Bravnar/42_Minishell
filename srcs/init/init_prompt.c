#include "minishell.h"

void	join_continued(char *final, t_main *shell)
{
	char	*one;

	one = ft_better_join(G_ARROW_SIGN, final);
	shell->prompt = ft_strdup(one);
	free(one);
}

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
		tmp = ft_better_join(result, "/");
		free(result);
		result = ft_better_join(tmp, part[i]);
		free (tmp);
	}
	tmp = ft_better_join("~", result);
	free(result);
	return (tmp);
}

void print_prompt_info(const char *prompt) 
{
    int visible_length = 0;
    int actual_length = strlen(prompt);
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

void	terminal_prompt(t_main *shell)
{
	char	**cwd;
	char	*tmp;
	char	*full_start;
	char	*end;
	char	*final;

	if (!shell->has_env)
		return ;
	if (shell->prompt)
		free(shell->prompt);
	cwd = ft_split(get_env(&shell->env, "PWD"), '/');
	// printf("len G_ARROW: %zu\n", ft_strlen(G_ARROW_SIGN));
	// printf("len MINISH: %zu\n", ft_strlen(MINISH));
	tmp = ft_better_join(G_ARROW_SIGN, MINISH);
	// printf("len tmp: %zu\n", ft_strlen(tmp));
	// printf("len EHL: %zu\n", ft_strlen(EHL));
	full_start = ft_better_join(tmp, EHL);
	// printf("len full_start: %zu\n", ft_strlen(full_start));
	free(tmp);
	tmp = join_prompt(cwd);
	ft_free_arr(cwd);
	end = ft_better_join(tmp, X_SIGN);
	final = ft_better_join(full_start, end);
	shell->prompt = ft_strdup(final);
	free(tmp);
	free(full_start);
	free(end);
	free(final);

	//print_prompt_info(shell->prompt);
}

/* 
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
	full = ft_better_join(intro, tmp);
	final = ft_better_join(full, X_SIGN);
	join_continued(final, shell);
	free(intro);
	free(final);
	free(full);
	free(tmp);
} */

/* void	terminal_prompt(t_main *shell)
{
	char	*cwd;
	char	*intro;
	char	*temp;

	if (!shell->has_env)
		return ;
	if (shell->prompt != NULL)
		free(shell->prompt);
	cwd = get_env(&shell->env, "PWD");
	intro = ft_better_join(G_ARROW_SIGN, SH);
	temp = ft_better_join(intro, cwd);
	free(intro);
	intro = ft_better_join(temp, X_SIGN);
	free(temp);
	shell->prompt = ft_strdup(intro);
	free(intro);
}
 */