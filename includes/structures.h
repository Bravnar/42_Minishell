/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:33 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/16 16:42:44 by smuravye         ###   ########.fr       */
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

typedef struct s_token
{
	char			*value;
	int				type;
	int				is_arg;
	struct s_token	*next;
	struct s_token	*prev;	
}					t_token;

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