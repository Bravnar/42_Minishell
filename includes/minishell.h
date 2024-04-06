/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:53:13 by smuravyev         #+#    #+#             */
/*   Updated: 2024/04/05 14:38:04 by smuravye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*----------------------------------------------------------------------------*/
/*                                  LIBRARIES                                 */
/*----------------------------------------------------------------------------*/

# include "../lib/includes/my_lib.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <unistd.h>
# include "colors.h"

/*----------------------------------------------------------------------------*/
/*                                  DEFINES                                   */
/*----------------------------------------------------------------------------*/

# define PROMPT "EHL_Bangers $ "
# define TRUE 1
# define FALSE 0

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
	int		count;
	char	**args_list;
	int		args_count;
	int		len;
}	t_parse;

/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

char	**mh_lex(char *u_input);

#endif