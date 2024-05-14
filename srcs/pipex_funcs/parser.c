#include "minishell.h"

int	count_args(const char *cmd)
{
	int	count;
	int	in_quotes;

	count = 0;
	if (!cmd)
		return (count);
	in_quotes = 0;
	while (*cmd == ' ')
		cmd++;
	while (*cmd)
	{
		if (!in_quotes && (*cmd == '\'' || *cmd == '\"'))
			in_quotes = *cmd;
		else if (in_quotes && (*cmd == in_quotes))
			in_quotes = 0;
		else if (*cmd == ' ' && !in_quotes)
		{
			count++;
			while (*cmd == ' ')
				cmd++;
			continue ;
		}
		cmd++;
	}
	return (count + 1);
}

char	*handle_space(char **cmd, t_px *px)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	px->len = 0;
	while (tmp[px->len] != ' ' && tmp[px->len] != '\0')
		px->len++;
	result = ft_substr(tmp, 0, px->len);
	*cmd += px->len;
	return (result);
}

char	*handle_quote(char **cmd, t_px *px)
{
	char	*tmp;
	char	*result;

	tmp = *cmd;
	px->len = 0;
	while (tmp[px->len] != px->q_char)
		px->len++;
	result = ft_substr(tmp, 0, px->len);
	*cmd += px->len + 1;
	px->q_char = 0;
	return (result);
}

char	**pipex_parse(char *s)
{
	t_px	px;

	px.i = 0;
	px.q_char = 0;
	px.count = count_args(s);
	px.cmd_s = malloc(sizeof(char *) * (px.count + 1));
	if (!px.cmd_s)
		return (NULL);
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!px.q_char && (*s == 34 || *s == 39))
		{
			px.q_char = *s;
			s++;
		}
		if (px.q_char)
			px.cmd_s[px.i++] = handle_quote(&s, &px);
		else if (!px.q_char && *s)
			px.cmd_s[px.i++] = handle_space(&s, &px);
	}
	px.cmd_s[px.i] = NULL;
	return (px.cmd_s);
}
