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
# include "structs.h"
// # include "structures.h"
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
# define SPECIAL_W_SPACE " $<>|;\'\""
# define REDIRS "<>"
# define PIPE "|"


/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

/* INIT */

t_main	*init_structs(char **envp);

/* ERRORS */

void	error_handler(t_err code);

/* LEXER MAIN*/

int		lexer(t_lex	*l);

/* LEXER FUNCS */

void	lex_input(t_lex *l, char *charset);

/* LEXER INFO FILL */

void	fill_info(t_lex *l);

/* LEXER LLIST UTILS */

void	print_list(t_llex **head);
void	free_tokens(t_llex *token_list);
void	add_token(t_llex **token_list, t_llex *new_token);
//t_llex	*new_token(char *value);
t_llex	*new_token(char *value,	int is_con);
int		ms_lstsize(t_llex *lst);

/* CHECK SYNTAX */

int		check_quotes(t_lex *l);
void	reset_quotes(t_lex *l);
int		check_redirs(t_lex *l);
int		check_pipes(t_lex *l);

/* ENV */

t_envp	*new_env_node(char *key, char *value);
void	add_env_node(t_envp **envp_head, t_envp *new_envp_node);
void	print_envp(t_envp **head);
void	populate_envp(t_main *shell);
t_envp	*get_env(t_envp **head, char *var);
void	free_nodes(t_envp *token_list);

/* CLEANUP */

void	free_lex(t_lex *lex);
void	free_cmds(t_cmds *cmds);
void	free_main(t_main *shell);

/* PARSER */

void	parser_logic(t_lex *l);
//void	parser_main(t_main *shell);
void	parser_main(t_lex *lex);
void	print_cmds(t_cmds **head);
void	add_cmd_node(t_cmds **envp_head, t_cmds *new_envp_node);
t_cmds	*new_cmd_node(char *key, char *value);

/* char	**mh_lex(char *u_input);
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

void	alt_lex(t_shell *main);
t_lex	*new_token(char *value);
void	add_token(t_lex **token_list, t_lex *new_token);
void	free_tokens(t_lex *token_list);
void	print_list(t_lex **head);
 */

/* Builtins */
void	pwd(void);
void	cd(char *dirname);
void	env(char **ENV);
void	echo(char **args, char **ENV);

#endif
