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

# define TRUE 1
# define FALSE 0
# define WHITESPACE " \t\n\r\f\v"
# define SPECIAL "<>|;"
# define QUOTES "\"\'"
# define SPECIAL_W_SPACE " $<>|;\'\""
# define REDIRS "<>"
# define PIPE "|"
# define PIPE_REDIRS "|<>"
# define DOLLAR_CHARS "$?-0123456789"
# define CANCEL_EXP "+~"
# define NO_HOME "HOME not defined"

/* PROMPT */

# ifdef __APPLE__

/* APPLE VERSION */

#  define APPLE 1

#  define MINISH "\033[01;37mminish\033[00m"
#  define EHL "\033[01;34mEHL:\033[00m"
#  define G_ARROW_SIGN "\033[01;32m➜\033[00m  "
#  define X_SIGN "\033[01;34m ✘ \033[00m"

// #  define MINISH "\001\033[01;37m\002minish\001\033[00m\002"
// #  define EHL "\001\033[01;34m\002EHL:\001\033[00m\002"
// #  define G_ARROW_SIGN "\001\033[01;32m\002➜\001\033[00m\002  "
// #  define X_SIGN "\001\033[01;34m\002 ✘ \001\033[00m\002"

/* NO ENV */

#  define FACE "\033[1;33m(\u256F\u00B0\u25A1\u00B0)\u256F"
#  define THROW "\033[1;37m \uFE35 | NO ENV |:\033[00m"
#  define X_YELLOW "\033[01;33m ✘ \033[00m"

# else

/* LINUX VERSION */

#  define APPLE 0

#  define MINISH "\001\033[01;37m\002minish\001\033[00m\002"
#  define EHL "\001\033[01;34m\002EHL:\001\033[00m\002"
#  define G_ARROW_SIGN "\001\033[01;32m\002➜\001\033[00m\002  "
#  define X_SIGN "\001\033[01;34m\002 ✘ \001\033[00m\002"

/* NO ENV LINUX */

#  define FACE "\001\x1B[1;33m\002(\u256F\u00B0\u25A1\u00B0)\u256F"
#  define THROW "\001\x1B[1;37m\002 \uFE35 | NO ENV |:\001\033[00m\002"
#  define X_YELLOW "\001\033[01;33m\002 ✘ \001\033[00m\002"

# endif

/* FOR ERRORS */
# define MSHELL "minishell: "
# define TOO_MANY_ARGS "too many arguments"
# define NO_DIR "no such file or directory"

/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------BUILTINS DIR------------------------------*/

/* Builtins */

/* void	pwd(void);
void	cd(char *dirname);
void	env(char **ENV);
void	echo(char **args, char **ENV); */

/*----------------------------------BUILTINS STAN DIR-------------------------*/

/* CD */

void	cd_new(t_main *shell, char **cmds);
int		cd_count(char **cmds);
void	adjust_pwd(t_main *shell, char *old_pwd);
void	swap_old_new(t_main *shell, char **cmds, char *old_pwd);
void	go_home(t_main *shell, char **cmds, char *cwd);

/* ENV */
void	print_envp(t_envp **head);


/* EXPORT */
void	export(t_main *shell, char **cmds);
void	sort_local_copy(t_envp	**local);
void	swap_nodes(t_envp *a, t_envp *b);
t_envp	*copy_list(t_envp *src);
void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr);
void	print_local_copy(t_envp **head);
int		count_export_args(char **cmds);
void	free_local_copy(t_envp *local);

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
void	set_env(t_envp **head, char *key, char *value);
void	make_no_env_prompt(t_main *shell);
void	add_env(t_main *shell, char *str);

/*----------------------------------ERRORS DIR--------------------------------*/

/* ERRORS */

void	error_handler(t_err code);

/*----------------------------------INIT DIR----------------------------------*/

/* INIT */

t_main	*init_structs(char **envp);
t_lex	*init_lex(void);

/* INIT_PROMPT */

void	terminal_prompt(t_main *shell);
void 	print_prompt_info(const char *prompt);
char	*join_prompt(char **part);

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

void	parser_main(t_main *shell);
void	parser_body(t_main *shell);

/* PARSER_CMDS */

char 	**create_cmd_arr(t_llex *tmp, t_main *shell, int count);
void	add_cmds_node(t_cmds **head, t_cmds *new_node);
t_cmds	*new_cmds_node(char **cmds, t_files *files, int index);
int		count_commands(t_llex *head);
char	*expand_if_needed(t_llex *iter, t_main *shell);

/* PARSER_FUNCS */

void	parser_logic(t_lex *l);
void	handle_pipe(t_llex **tmp);
void	handle_complex_redirs(t_llex *tmp);
void	handle_complex_redirs(t_llex *tmp);

/* PARSER FILES */

t_files	*create_files_list(t_llex **tmp, t_main *shell);
void	add_file_node(t_files **file_head, t_files *new_file);
t_files	*new_file_node(t_llex *llex, t_main *shell);

/* PARSER FREE */

void	clear_t_cmds(t_main *shell);
void	free_cmds_nodes(t_cmds *head);
void	free_files_nodes(t_files *head);

/*----------------------------------SYNTAX DIR--------------------------------*/

/* CHECK SYNTAX */

int		check_quotes(t_lex *l);
void	reset_quotes(t_lex *l);
int		check_redirs(t_lex *l);
int		check_pipes(t_lex *l);

#endif

// # define SHELL "\x1B[1;37mminish\x1B[1;34mEHL:\x1B[0m"
// # define G_ARROW_SIGN "\001\033[1;32m\002\u279c\001\033[0m  "
// # define R_ARROW_SIGN "\033[1;31m\u279c\033[0m  "
// # define SPACE_SIGN "\001\033[1;96m\002 "
// # define X_SIGN " \033[1;34m\002\u2718\001\033[0m\002 "

// # define SHELL "\001\x1B[1;37m\002minish\001\x1B[1;34m\002EHL:\001\x1B[0m\002"

// # define MINISH "\001\e\[1m\e[37m\002\001minish\002"
// # define EHL "\001\e\[1m\e[34m\002\001EHL:\002\001\e[0m\002"
// # define G_ARROW_SIGN "\001\e[1m\e[32m\002\001\u279c\002\001 \002"
// # define X_SIGN "\001\e[1m\e[34m\002\001 \002\001\u2718\002\001 \002\001\e[0m\002"


// # define MINISH "\001\033[1;37m\002minish"
// # define EHL "\001\033[1;34m\002EHL:\001\033[0m\002"
// # define G_ARROW_SIGN "\001\033[1;32m\002➜\001\033[0m\002  "
// //# define G_ARROW_SIGN "\001\u279c\002"
// # define X_SIGN "\001\033[1;34m\002 ✘ \001\033[0m\002"

