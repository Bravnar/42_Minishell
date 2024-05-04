/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bravnar <bravnar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:31:34 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/04 15:06:28 by bravnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *err)
{
	while(*err)
		write(STDERR_FILENO, err++, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error_handler(t_err code)
{
	if (code == BAD_QUOTES)
		print_error("bash: error near unrecognized token");
}