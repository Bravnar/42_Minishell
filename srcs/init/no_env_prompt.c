#include "minishell.h"

/* void	make_no_env_prompt(t_main *shell)
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
} */

void	no_env_prompt(t_main *shell)
{
	char	*cwd;
	char	*tmp;
	char	*full_start;
	char	*end;
	char	*final;

	if (shell->prompt)
		free(shell->prompt);
	cwd = ft_strdup(get_env(&shell->env, "PWD"));
	tmp = ft_better_join(G_ARROW_SIGN, FACE);
	full_start = ft_better_join(tmp, THROW);
	free(tmp);
	//tmp = cwd;
	// ft_free_arr(cwd);
	end = ft_better_join(cwd, X_YELLOW);
	final = ft_better_join(full_start, end);
	shell->prompt = ft_strdup(final);
	//free(tmp);
	free(full_start);
	free(end);
	free(final);
	free(cwd);
	//print_prompt_info(shell->prompt);
}