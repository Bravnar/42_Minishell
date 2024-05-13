/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:11:43 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/20 17:11:51 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	print_env_var(char *str, int *j, char **ENV)
{
	int		i;
	int		len;
	char	*varname;

	if (str[*j] == '$')
	{
		if (!ft_strlen(str) - 1)
			printf("$");
		else
		{
			i = 0;
			varname = ft_split(str + 1, ' ')[0];
			len = ft_strlen(varname) - 1;
			if (!ft_strncmp("path", varname, len))
				varname = ft_strtoupper(varname);
			while (ENV[i] && !ft_strncmp(varname, ENV[i], len))
				i++;
			if (ENV[i])
				printf("%s", ft_split(ENV[i], '=')[1]);
			(*j) += len + 1;
		}
	}
	else
		printf("%c", str[*j]);
}

void	echo(char **args, char **ENV)
{
	int		i;
	int		j;
	bool	newline;
	bool	start;

	i = -1;
	newline = true;
	start = false;
	while (args[++i])
	{
		if (!start && !ft_strncmp(args[i], "-n", 2))
		{
			newline = ft_strncmp(args[i], "-n", 2);
			continue ;
		}
		else
			start = true;
		j = -1;
		while (args[i][++j])
			print_env_var(args[i], &j, ENV);
		if (args[i][j + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
