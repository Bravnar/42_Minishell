/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:56:10 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/12 14:08:39 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes2(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] && ft_strchr(QUOTES, str[i]))
			count++;
	}
	return (count);
}