/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:17:34 by smuravyev         #+#    #+#             */
/*   Updated: 2024/05/03 16:15:44 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALT_STRUCTS_H
# define ALT_STRUCTS_H

typedef enum e_type
{
	CMD,
	ARG,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	APPEND,
	HEREDOC,
	CMD_FULL,
}	t_type;

typedef struct s_lex_info
{
	int		i;
	char	q_char;
	int		backslash;
	int		count;
	int		token_len;
	int		len;
	char	*cur;
	char	*token;
}	t_lex_info;

typedef struct s_lex
{
	char			*value;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;

typedef struct s_token
{
	char	*value;
	int		needs_expansion;
	int		is_in_quotes;
	t_type	tok_type;
	int		index;
	struct s_token	*next;
	struct s_token	*prev;	
}	t_token;

typedef	struct s_cmd_tbl
{
	t_token				*group;
	t_type				group_type;
	int					index;
	struct s_cmd_tbl	*next;
	struct s_cmd_tbl	*prev;
}	t_cmd_tbl;

typedef struct s_shell
{			
	int					ac;
	char				**av;
	char				**env;
	char				*user_input;
	char				*trimmed_input;
	char				*prompt;
	t_lex				*lexems;
	t_lex_info			*lex_info;
	t_token				*tokens;
	t_cmd_tbl			*cmd_tbl;
}	t_shell;

#endif