/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:57:14 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/25 17:57:14 by smuravye         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp(t_envp *env)
{
	t_envp	*tmp;
	int		count;

	tmp = env;
	count = 0;
	while (tmp)
	{
		if (tmp->printable == 1 || tmp->printable == 2)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**back_to_array(t_envp *env)
{
	t_envp	*tmp;
	char	**result;
	char	*tmp_join;
	int		count;
	int		i;

	tmp = env;
	count = count_envp(tmp);
	i = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (tmp)
	{
		if (tmp->printable == 1 || tmp->printable == 2)
		{
			tmp_join = ft_better_join(tmp->key, "=", 0);
			result[i++] = ft_better_join(tmp_join, tmp->value, 0);
			free(tmp_join);
		}
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}
