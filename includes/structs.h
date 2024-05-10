/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:06:51 by bravnar           #+#    #+#             */
/*   Updated: 2024/05/10 16:39:42 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	NONE,
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

typedef enum e_err
{
	NO_ERR,
	BAD_QUOTES,
	BAD_REDIRS,
	BAD_PIPES,
	BAD_REDIRS_NL,
}	t_err;

typedef struct s_llex
{
	char			*value;
	char			is_in_quotes;
	int				index;
	int				needs_exp;
	t_type			type;
	struct s_llex	*next;
	struct s_llex	*prev;
}	t_llex;

typedef struct s_lex
{
	int				i;
	int				j;
	int				s_quotes;
	int				d_quotes;
	int				s_count;
	int				d_count;
	char			q_char;
	int				backslash;
	int				token_len;
	int				word_len;
	char			*input;
	char			*trim;
	char			*token;
	int				err_code;
	t_llex			*link;
}	t_lex;

typedef struct s_tok
{
	char			*value;
	int				needs_expansion;
	char			is_in_quotes;
	int				index;
	t_type			type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

typedef struct s_cmds
{
	t_tok			*group;
	t_type			type;
	int				index;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_main
{
	int				ac;
	char			**av;
	char			**env;
	char			*prompt;
	t_lex			*l;
	t_tok			*tok;
	t_cmds			*cmds;
}	t_main;

#endif