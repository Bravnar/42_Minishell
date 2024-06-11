/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:20:45 by smuravye          #+#    #+#             */
/*   Updated: 2024/06/07 13:37:29 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

/* int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
} */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	// if (!s2 && !s1)
	// 	return (0);
	// if (!s1)
	// 	return (s2[0]);
	// if (!s2)
	// 	return (s1[0]);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
