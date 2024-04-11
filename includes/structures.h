/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:33 by smuravye          #+#    #+#             */
/*   Updated: 2024/04/11 18:19:09 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*----------------------------------------------------------------------------*/
/*                                 STRUCTURES                                 */
/*----------------------------------------------------------------------------*/

typedef struct s_llist
{
	char			*str;
	int				index;
	struct s_list	*prev;
	struct s_list	*next;
}	t_llist;

typedef struct s_main
{
	char			*input;
	bool			is_cmd;
	bool			is_arg;
	struct s_list	*l_list;
}	t_main;

typedef struct s_parse
{
	int		i;
	char	q_char;
	int		backslash; // how?
	int		count;
	char	*work_line;
	char	**args;
	int		token_len;
	int		args_count;
	int		len;
	int		invalid_token;
	int		invalid_quote;
}	t_parse;

#endif