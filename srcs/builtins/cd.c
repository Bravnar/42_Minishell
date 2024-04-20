/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:57:02 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/20 14:57:02 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char* dirname)
{
	if (chdir(dirname) != 0)
	{
		printf("cd: no such file or directory: %s", dirname);
		exit(2);
	}
}
