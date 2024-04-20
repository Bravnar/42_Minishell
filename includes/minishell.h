/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:38:59 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/20 14:38:59 by hmorand          ###   ########.ch       */
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

# define PROMPT CYAN"EHL_Bangers $ "RESET
# define TRUE 1
# define FALSE 0
# define WHITESPACE " \t\n\r\f\v"
# define SPECIAL "<>|;"
# define QUOTES "\"\'"
# define SPECIAL_W_SPACE " <>|;\'\""
# define REDIRS "<>"
# define PIPE "|"


/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

char	**mh_lex(char *u_input);
char	**lex(char *input);
char	**ft_shellsplit(char *str, char *charset);
char	*save_str(char *str, char *charset);
int		count_args(char *str, char *charset);
int		count_quotes2(char *str);

/* New tokenizer */

/* Linked list funcs */
t_token	*lex_input(char *input);
t_token	*new_token(char *value);
void	add_token(t_token **token_list, t_token *new_token);
void	free_tokens(t_token *token_list);
void	print_list(t_token **head);

/* Helper funcs */
int		strlen_til_sep(char *str, char *charset);
int		is_in_charset(char c, char *charset);
int		check_before(char *input, t_quotes *q);
int		check_quotes(char *input, t_quotes *q);

/* Builtins */
void	pwd(void);

#endif
