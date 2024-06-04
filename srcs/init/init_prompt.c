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

	if (!shell->has_env)
	{
		make_no_env_prompt(shell);
		return ;
	}
	if (shell->prompt)
		free(shell->prompt);
	cwd = ft_split(get_env(&shell->env, "PWD"), '/');
	tmp = ft_better_join(G_ARROW_SIGN, MINISH);
	full_start = ft_better_join(tmp, EHL);
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
}
