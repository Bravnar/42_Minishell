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

/*----------------------------------BUILTINS DIR------------------------------*/

/* Builtins */

void	pwd(void);
void	cd(char *dirname);
void	env(char **ENV);
void	echo(char **args, char **ENV);

/*----------------------------------CLEANUP DIR-------------------------------*/

/* CLEANUP */

void	free_lex(t_lex *lex);
void	free_cmds(t_cmds *cmds);
void	free_main(t_main *shell);

/*----------------------------------ENV DIR-----------------------------------*/

/* ENV */

t_envp	*new_env_node(char *key, char *value);
void	add_env_node(t_envp **envp_head, t_envp *new_envp_node);
void	print_envp(t_envp **head);
void	populate_envp(t_main *shell);
char	*get_env(t_envp **head, char *var);
void	free_nodes(t_envp *token_list);

/*----------------------------------ERRORS DIR--------------------------------*/

/* ERRORS */

void	error_handler(t_err code);

/*----------------------------------INIT DIR----------------------------------*/

/* INIT */

t_main	*init_structs(char **envp);

/*----------------------------------LEXER DIR---------------------------------*/

/* LEXER MAIN*/

//int		lexer(t_lex	*l);
int		lexer(t_lex	*l, t_main *shell);

/* LEXER FUNCS */

void	lex_input(t_lex *l, char *charset);
void	handle_quotes(t_lex *l);
void	handle_other(t_lex *l, char *charset);
void	handle_special(t_lex *l);
void	handle_dollar(t_lex *l);

/* LEXER INFO FILL */

void	fill_info(t_lex *l);
void	work_args(t_llex *tmp);

/* LEXER LLIST UTILS */

void	print_list(t_llex **head);
void	free_tokens(t_llex *token_list);
void	add_token(t_llex **token_list, t_llex *new_token);
//t_llex	*new_token(char *value);
t_llex	*new_token(char *value,	int is_con);
int		ms_lstsize(t_llex *lst);

/*----------------------------------MAIN DIR----------------------------------*/

int		main(int ac, char **av, char **envp);
void	gameplay_loop(t_main *shell);
void	free_all(t_main *shell);

/*----------------------------------PARSER DIR--------------------------------*/

/* PARSER_MAIN */

// void	parser_main(t_lex *lex);
void	parser_main(t_main *shell);
void	parser_create_cmds(t_main *shell);

/* PARSER_CMDS */

char	**create_cmd_arr(t_llex *tmp, t_main *shell, int count);
void	add_cmds_test(t_cmds **head, t_cmds *new_node);
t_cmds	*new_cmds_test(char **cmds, t_files *files, int index);
int		count_commands(t_llex *head);

/* PARSER_FUNCS */

void	parser_logic(t_lex *l);
void	handle_pipe(t_llex **tmp);
void	handle_complex_redirs(t_llex *tmp);
void	handle_complex_redirs(t_llex *tmp);

/* PARSER LINKED UTILS */

void	print_cmds(t_cmds **head);
void	add_cmd_node(t_cmds **envp_head, t_cmds *new_envp_node);
t_cmds	*new_cmd_node(char *key, char *value);

/* PARSER FILES */

t_files	*get_files(t_llex **head, t_main *shell);
void	free_files(t_files *files_list);
void	add_file(t_files **file_head, t_files *new_file);
t_files	*new_file(t_llex *llex, t_main *shell);

/* PARSER TEST */

void	parser_test(t_main *shell);

/*----------------------------------SYNTAX DIR--------------------------------*/

/* CHECK SYNTAX */

int		check_quotes(t_lex *l);
void	reset_quotes(t_lex *l);
int		check_redirs(t_lex *l);
int		check_pipes(t_lex *l);

#endif
