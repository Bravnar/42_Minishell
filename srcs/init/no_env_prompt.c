/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 25/06/2024 06:36:25 by smuravye          #+#    #+#             */
/*   Updated: 25/06/2024 15:03:19 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tmp = ft_better_join(G_ARROW_SIGN, FACE, 0);
	full_start = ft_better_join(tmp, THROW, 0);
	free(tmp);
	end = ft_better_join(cwd, X_YELLOW, 0);
	final = ft_better_join(full_start, end, 0);
	shell->prompt = ft_strdup(final);
	free(full_start);
	free(end);
	free(final);
	free(cwd);
}

/* void	make_no_env_prompt(t_main *shell)
{
	char	*cwd;
	char	*first_part;
	char	*second_part;
	char	*final;

	if (shell->prompt)
		free(shell->prompt);
	cwd = my_get_path();
	first_part = ft_better_join(FACE, THROW, 0);
	second_part = ft_better_join(first_part, cwd, 0);
	final = ft_better_join(second_part, X_YELLOW, 0);
	shell->prompt = ft_strdup(final);
	free(cwd);
	free(first_part);
	free(second_part);
	free(final);
} */