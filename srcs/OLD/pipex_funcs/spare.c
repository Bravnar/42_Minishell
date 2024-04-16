/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spare.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:36:47 by smuravyev         #+#    #+#             */
/*   Updated: 2024/04/02 13:15:13 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **av, int *end, char **envp)
{
	int	fd;

	fd = my_open(av[1], 'i');
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	exec(av[2], envp);
}

void	parent(char **av, int *end, char **envp)
{
	int	fd;

	fd = my_open(av[4], 'o');
	dup2(fd, 1);
	dup2(end[0], 0);
	close(end[1]);
	exec(av[3], envp);
}
/* void	child0(char **av, int *end, char **envp)
{
	int	fd;

	fd = my_open(av[1], 'i');
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	exec(av[2], envp);
}

void	child1(char **av, int *end, char **envp)
{
	int	fd;

	fd = my_open(av[4], 'o');
	dup2(fd, 1);
	dup2(end[0], 0);
	close(end[1]);
	exec(av[3], envp);
} */

int	main(int ac, char **av, char **env)
{
	int		end[2];
	pid_t	pid;

	if (!env || !*env)
		return (0);
	if (ac == 5)
	{
		if (pipe(end) == -1)
			exit(-1);
		pid = fork();
		if (pid == -1)
			exit(-1);
		if (!pid)
			child(av, end, env);
		parent(av, end, env);
	}
	perror("pipex: invalid parameters");
	exit(1);
}
