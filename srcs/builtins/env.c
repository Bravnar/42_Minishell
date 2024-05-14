/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:54:29 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/20 16:54:29 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **ENV)
{
	int	i;

	i = -1;
	while (ENV[++i])
		printf("%s\n", ENV[i]);
}
/*
int	main(int argc, char *argv[], char *ENV[])
{
	(void) argv;
	(void) argc;

	env(ENV);
	return (-1);
} */
