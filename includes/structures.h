/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:33 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/30 13:45:41 by smuravyev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*----------------------------------------------------------------------------*/
/*                                 STRUCTURES                                 */
/*----------------------------------------------------------------------------*/

typedef enum e_type
{
	CMD,
	ARGS,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	APPEND_IN,
	APPEND_OUT,
}	t_type;

typedef enum e_error
{
	QUOTES_ERR,
	REDIR_ERR,
	PIPE_ERR,
}	t_error;

/* USED */

typedef struct s_token
{
	char			*value;
	int				has_space_before;
	int				has_space_after;
	struct s_token	*next;
	struct s_token	*prev;	
}					t_token;

/* USED */

typedef struct s_parse_prep
{
	t_type				type;
	int					has_quote;
	int					needs_expand;
	int					index;
	struct s_parse_prep	*next;
	struct s_parse_prep *prev;
}	t_parse_prep;

typedef struct s_main
{
	char			*input;
	bool			is_cmd;
	bool			is_arg;
	struct s_list	*l_list;
}	t_main;

typedef struct s_quotes
{
	int	count_s;
	int	count_d;
	int	in_single;
	int	in_double;
}	t_quotes;

/* USED */

typedef struct s_parse
{
	int			i;
	char		q_char;
	int			backslash; // how?
	int			count;
	char		*work_line;
	int			token_len;
	int			len;
	t_quotes	quotes;
}	t_parse;

#endif