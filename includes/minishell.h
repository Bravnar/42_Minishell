/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuravyev <smuravyev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:53:13 by smuravyev         #+#    #+#             */
/*   Updated: 2024/05/03 18:23:07 by smuravyev        ###   ########.fr       */
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
/* # include "alt_structs.h" */

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

t_token	*lex_input(char *input);
t_token	*new_token(char *value);
void	add_token(t_token **token_list, t_token *new_token);
void	free_tokens(t_token *token_list);
void	print_list(t_token **head);

int		strlen_til_sep(char *str, char *charset);
int		is_in_charset(char c, char *charset);

char	*get_exec_path(char *cmd, char **env);
void	free_arr(char **arr);
char	*get_path_line(char **envp);
int		check_quotes(char *input, t_quotes *q);


/* void	alt_lex(t_shell *main);
t_lex	*new_token(char *value);
void	add_token(t_lex **token_list, t_lex *new_token);
void	free_tokens(t_lex *token_list);
void	print_list(t_lex **head);
 */

#endif