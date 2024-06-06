#include "minishell.h"


char	*ft_strreplace(char *input, char *to, char *by, int index)
{
	char	*result;
	int		i;
	int		j;
	int		new_len;

	new_len = ft_strlen(by) - ft_strlen(to) + ft_strlen(input) + 1;
	result = malloc(sizeof(char) * new_len);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < index)
		result[i] = input[i];
	j = -1;
	while (by[++j])
		result[i + j] = by[j];
	input += ft_strlen(to);
	while (i + j < new_len - 1)
	{
		result[i + j] = input[i];
		i++;
	}
	result[i + j] = '\0';
	printf("input var: %s\n", input);
	free(input);
	input = NULL;
	return (result);
}

char	*var_replace(char *input, t_main *shell)
{
	char	*result;
	char	*var;
	char	*to_replace;
	int		i;
	int		j;

	i = 0;
	result = ft_strdup(input);
	while (result[i])
	{
		while (result[i] != '$')
		{
			if (!result[i])
				break ;
			i++;
		}
		j = 1;
		if (!result[i])
			break ;
		while (ft_isalnum(result[i + j]) || result[i + j] == '_')
			j++;
		to_replace = ft_strndup(result + i, j);
		var = get_env(&shell->env, to_replace);
		if (var)
		{
			result = ft_strreplace(result, to_replace, var, i);
			i += ft_strlen(var);
		}
		else if (result[i] != '\0')
			i++;
		free(to_replace);
	}
	return (result);
}
