/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravye <smuravye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:53:13 by smuravyev         #+#    #+#             */
/*   Updated: 2024/04/11 18:56:20 by smuravye         ###   ########.fr       */
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
# include "structures.h"

/*----------------------------------------------------------------------------*/
/*                                  DEFINES                                   */
/*----------------------------------------------------------------------------*/

# define PROMPT "EHL_Bangers $ "
# define TRUE 1
# define FALSE 0
# define WHITESPACE " \t\n\r\f\v"
# define SPECIAL "<>|;"
# define QUOTES "\"\'"
# define SPECIAL_W_SPACE " <>|;"
# define REDIRS "<>"
# define PIPE "|"


/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

char	**mh_lex(char *u_input);
char	**lex(char *input);
char	**ft_shellsplit(char *str, char *charset);
int		is_in_charset(char c, char *charset);
int		strlen_til_sep(char *str, char *charset);
char	*save_str(char *str, char *charset);
int		count_args(char *str, char *charset);

#endif