/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:50:32 by hmorand           #+#    #+#             */
/*   Updated: 2024/06/24 13:50:32 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strreplace(char *input, char *to, char *by, int *index)
{
	char	*result;
	int		i;
	int		j;
	int		new_len;
	int		len_to;

	new_len = ft_strlen(by) - ft_strlen(to) + ft_strlen(input) + 1;
	result = malloc(sizeof(char) * new_len);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < *index)
		result[i] = input[i];
	j = -1;
	while (by[++j])
		result[i + j] = by[j];
	len_to = ft_strlen(to);
	while (i + j < new_len - 1)
	{
		result[i + j] = input[i + len_to];
		i++;
	}
	result[i + j] = '\0';
	free(input);
	return (result);
}

char	*check_replace(int *i, char *result, t_main *shell)
{
	int		j;
	char	*to_replace;
	char	*var;

	j = 1;
	while (ft_isalnum(result[*i + j]) || result[*i + j] == '_')
		j++;
	to_replace = ft_strndup(result + *i, j);
	var = get_env(&shell->env, to_replace);
	if (var)
		result = ft_strreplace(result, to_replace, var, i);
	else if (result[*i] != '\0')
		(*i)++;
	*i += ft_strlen(var);
	free(to_replace);
	return (result);
}

char	*var_replace(char *input, t_main *shell)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup(input);
	if (!result)
		return (NULL);
	while (result[i])
	{
		while (result[i] != '$')
		{
			if (!result[i])
				break ;
			i++;
		}
		if (!result[i])
			break ;
		result = check_replace(&i, result, shell);
	}
	return (result);
}
