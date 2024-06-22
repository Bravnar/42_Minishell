#include "minishell.h"

static void	toll_space_sign(const char **sptr, int *sign)
{
	while (ft_isspace(**sptr))
		(*sptr)++;

	if (ft_strchr("+-", **sptr))
	{
		if (**sptr == '-')
			*sign = -1;
		(*sptr)++;
	}
}

static long long	final_decision(t_strtoll strtoll, char **endptr, const char *nptr)
{
	if (strtoll.digit_count == 0)
	{
		errno = EINVAL;
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	if (endptr)
		*endptr = (char *)strtoll.s;
	return (strtoll.sign * strtoll.result);
}

long long	ft_strtoll(const char *nptr, char **endptr)
{
	t_strtoll	strtoll;

	ft_bzero(&strtoll, sizeof(t_strtoll));
	strtoll.sign = 1;
	strtoll.s = nptr;
	toll_space_sign(&strtoll.s, &strtoll.sign);
	while (ft_isdigit(*strtoll.s))
	{
		strtoll.digit = *strtoll.s - '0';
		if (strtoll.result > LLONG_MAX / 10 ||
		(strtoll.result == LLONG_MAX / 10 && strtoll.digit > LLONG_MAX % 10))
		{
			errno = ERANGE;
			if (endptr)
				*endptr = (char *)strtoll.s;
			if (strtoll.sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		strtoll.result = strtoll.result * 10 + strtoll.digit;
		strtoll.s++;
		strtoll.digit_count++; 
	}
	return (final_decision(strtoll, endptr, nptr));
	
}

int	my_exit(t_main *shell, char **cmds)
{
	long long	exit_status;
	char		*endptr;

	exit_status = 0;
	ft_fprintf(2, "exit\n");
	if (cmds && cmds[1])
	{
		errno = 0;
		exit_status = ft_strtoll(cmds[1], &endptr);
		if (errno == ERANGE || errno == EINVAL || *endptr != '\0')
		{
			ft_fprintf(2, "%s%s: %s: %s\n", MSHELL, cmds[0], cmds[1], NUM_ARG);
			exit_status = 2;
		}
		else if (cmds[2])
		{
			ft_fprintf(2, "%s%s: %s\n", MSHELL, cmds[0], TOO_MANY_ARGS);
			return (EXIT_FAILURE);
		}
	}
	free_all(shell);
	clear_t_cmds(shell);
	free_main(shell);
	exit((unsigned char)exit_status);
}
