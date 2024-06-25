#ifndef MINISHELL_H
# define MINISHELL_H

/*----------------------------------------------------------------------------*/
/*                                  LIBRARIES                                 */
/*----------------------------------------------------------------------------*/

# define _POSIX_C_SOURCE 200809L
# define _XOPEN_SOURCE 700

# include "../lib/includes/my_lib.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>
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
# define SPECIAL "<>|"
# define QUOTES "\"\'"
# define SPECIAL_W_SPACE " $<>|\'\""
# define REDIRS "<>"
# define PIPE "|"
# define PIPE_REDIRS "|<>"
# define DOLLAR_CHARS "$?-0123456789"
# define SYNTAX_STOP "&;`()"
# define CANCEL_EXP "+~"
# define NO_HOME "HOME not defined"
# define ENVLIN "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define SH "minishell:"
# define NOT_SET "HOME not set"

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

/* #  define FACE "\001\033[1;33m\002(\u256F\u00B0\u25A1\u00B0)\u256F"
#  define THROW "\001\033[1;37m\002 \uFE35 | NO ENV |:\001\033[00m\002"
#  define X_YELLOW "\001\033[01;33m\002 ✘ \001\033[00m\002" */

#  define FACE "\001\033[01;33m\002(╯°□°)╯\001\033[00m\002"
#  define THROW "\001\033[01;37m\002︵| NO ENV |:\001\033[00m\002"
#  define X_YELLOW "\001\033[01;33m\002 ✘ \001\033[00m\002"

# endif

/* FOR ERRORS */
# define MSHELL "minishell: "
# define TOO_MANY_ARGS "too many arguments"
# define NO_DIR "no such file or directory"

# define QUOTES_ERR "Mismatched quotation marks."
# define REDIR_IN_ERR "syntax error near unexpected token '<'"
# define REDIR_OUT_ERR "syntax error near unexpected token '>'"
# define PIPE_ERR "syntax error near unexpected token '|'"
# define NEWLINE_ERR "syntax error near unexpected token 'newline'"
# define APPEND_ERR "syntax error near unexpected token '>>'"
# define HEREDOC_SIGN_ERR "syntax error near unexpected token '<<'"
# define SIMPLE_SYNTAX "syntax error: forbidden character"
# define EXPORT_SIGN "'=': not a valid identifier"
# define NUM_ARG "numeric argument required"

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

int		cd_new(t_main *shell, char **cmds);
int		cd_count(char **cmds);
void	adjust_pwd(t_main *shell, char *old_pwd);
void	swap_old_new(t_main *shell, char **cmds, char *old_pwd);
void	go_home(t_main *shell, char **cmds, char *cwd);

/* ENV */
void	free_local_copy(t_envp *local);
int		count_export_args(char **cmds);
void	print_local_copy(t_envp **head, int fd);
void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr);

int		print_envp(t_envp **head, int fd);

/* EXPORT */
int		export(t_main *shell, char **cmds, int fd);
void	sort_local_copy(t_envp	**local);
void	swap_nodes(t_envp *a, t_envp *b);
t_envp	*copy_list(t_envp *src);
void	copy_work(t_envp *n_n, t_envp **l_h, t_envp **l_t, t_envp *curr);
int		count_export_args(char **cmds);
void	free_local_copy(t_envp *local);
char	**export_split(char *str);

/* ECHO */
int		my_echo(char **cmds, int fd);

/* UNSET */

int		unset_env(char **cmds, t_envp **head);

/* PWD */

int		my_pwd(int fd, t_main *shell, char **cmds);

/* EXIT */

int		my_exit(t_main *shell, char **cmds);

/*----------------------------------CLEANUP DIR-------------------------------*/

/* CLEANUP */

void	free_lex(t_lex *lex);
void	free_cmds(t_cmds *cmds);
void	free_main(t_main *shell);

/*----------------------------------ENV DIR-----------------------------------*/

/* ENV */

char	*my_get_path(void);
void	no_env_handle(t_main *shell);
t_envp	*new_env_node(char *key, char *value);
void	add_env_node(t_envp **envp_head, t_envp *new_envp_node);
void	populate_envp(t_main *shell);
void	free_nodes(t_envp *token_list);
// void	make_no_env_prompt(t_main *shell);
char	*handle_tilde(t_envp **head, char *var);
char	*handle_quote(t_envp **head, char *var);

/* ENV GET SET */

void	add_env(t_main *shell, char *str);
void	set_env(t_envp **head, char *key, char *value, int print);
char	*get_env(t_envp **head, char *var);
void	set_underscore(t_cmds *cmds, t_main *shell);

/* NO ENV PROMPT */

void	no_env_prompt(t_main *shell);
char	**back_to_array(t_envp *env);

/*----------------------------------ERRORS DIR--------------------------------*/

/* ERRORS */

void	error_handler(t_err code, char *file, t_main *shell);

/*----------------------------------INIT DIR----------------------------------*/

/* INIT */

t_main	*init_structs(char **envp);
t_lex	*init_lex(void);

/* INIT_PROMPT */

void	terminal_prompt(t_main *shell);
void	print_prompt_info(const char *prompt);
char	*join_prompt(char **part, t_main *shell);
t_envp	*new_no_env_node(char *key, char *value, int print);
void	make_no_env_prompt(t_main *shell);

/*----------------------------------LEXER DIR---------------------------------*/

/* LEXER MAIN*/

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
t_llex	*new_token(char *value,	int is_con);
int		ms_lstsize(t_llex *lst);

/*----------------------------------MAIN DIR----------------------------------*/

int		main(int ac, char **av, char **envp);
void	gameplay_loop(t_main *shell);
void	free_all(t_main *shell);

/*----------------------------------PARSER DIR--------------------------------*/

/* VAR REPLACE */

char	*ft_strreplace(char *input, char *to, char *by, int *index);
char	*check_replace(int *i, char *result, t_main *shell);
char	*var_replace(char *input, t_main *shell);

/* PARSER EXP COMB */

char	*expand_if_needed(t_llex *iter, t_main *shell);
void	expand_and_replace(t_llex *iter, t_main *shell);
void	combine_with_prev(t_llex *iter);
void	parser_combiner(t_main *shell);

/* PARSER_CMDS */

int		count_commands(t_llex *head);
char	**duplicate_cmds(char **cmds);
t_cmds	*new_cmds_node(char **cmds, t_files *files, int index, t_main *shell);
void	add_cmds_node(t_cmds **head, t_cmds *new_node);
char	**create_cmd_arr(t_llex *tmp, t_main *shell, int count);

/* PARSER FILES */

t_files	*new_file_node(t_llex *llex, t_main *shell);
void	add_file_node(t_files **file_head, t_files *new_file);
t_files	*create_files_list(t_llex **tmp, t_main *shell);

/* PARSER FREE */

void	free_files_nodes(t_files *head);
void	free_cmds_nodes(t_cmds *head);
void	clear_t_cmds(t_main *shell);

/* PARSER_FUNCS */

void	handle_simple_redirs(t_llex *tmp); //needs refactoring
void	handle_complex_redirs(t_llex *tmp); //needs adapting and refactoring!
void	handle_pipe(t_llex **tmp);
void	parser_logic(t_lex *l);

/* PARSER_MAIN */

void	print_main_struct(t_cmds **main);
void	parser_body(t_main *shell);
void	parser_main(t_main *shell);

/* PARSER PATH */

char	**get_paths(t_main *shell);
char	*get_path(char **paths, char *command);

/* PARSER PATCH */

void	patch_commands(char ***cmds);

/*----------------------------------SIGNALS DIR-------------------------------*/

/* HANDLE SIGNALS */

// void	sig_handler(int status);
// int		is_interactive(void);
// void	backslash_handler(int status);
// void	signals_main(int interactive);
// pid_t	pid_for_signal(pid_t *new);
// void	init_termios(void);
// void	signal_daddy(t_main *shell);
// void 	setup_heredoc_signals(void);

pid_t	pid_for_signal(pid_t *new);
int		send_err_code(int *new_err);
int		is_vscode_terminal(t_main *shell);
void	heredoc_sigint_handler(int signum);
void	main_sigint_handler(int signum);
void	proc_sigint_handler(int signum);
void	proc_sigquit_handler(int signum);
void	sigaction_hd(void);
void	sigaction_main(t_main *shell);
void	sigaction_proc(void);
void	subshell_handle(int signum);

/*----------------------------------SYNTAX DIR--------------------------------*/

/* CHECK SYNTAX */

int		check_quotes(t_lex *l);
void	reset_quotes(t_lex *l);
int		check_redirs(t_lex *l);
int		check_pipes(t_lex *l);
int		check_spec(t_lex *l);

/* CHECK SYNTAX UTILS */

int		is_first(t_llex *l);
int		is_last(t_llex *l);
int		set_err_code(char *value);

/*--------------------------------EXECUTION DIR-------------------------------*/

/* MAIN */

int		execute(t_cmds *cmds, t_main *shell);
int		execute_cmd(t_cmds *cmds, t_main *shell, int fd);
int		exec_single(t_cmds *cmds, pid_t *cpids, t_main *shell);

/* CHECKS */

int		is_bad_command(t_cmds *cmds, t_main *shell);
int		check_files(t_main *shell, t_cmds *cmds);

/* HEREDOC */

t_files	*extract_heredoc(t_files *file, t_main *shell);

/* PIPING UTILS */

int		exec_pipeline_first(t_cmds *cmds, pid_t *cpids, t_main *shell);
int		exec_pipeline_last(t_cmds *cmds,
			int fd_in, pid_t *cpids, t_main *shell);
int		exec_pipeline_middle(t_cmds *cmds,
			int fd_in, pid_t *cpids, t_main *shell);
void	piping(t_cmds *tmp, pid_t *cpids, int *fd_in, t_main *shell);

/* PID_UTILS */

void	add_pid(pid_t pid, pid_t *cpids);
int		wait_for_children(pid_t *cpids, t_main *shell);
void	determine_err(t_main *shell, int status);
int		send_err_code(int *new_err);

/*-------------------------------BUILTIN SUBDIR------------------------------*/

/* BUILTINS */

int		builtins(t_cmds *cmds, t_main *shell, int fd);
int		exec_single_builtin(t_cmds *cmds, t_main *shell);
int		is_builtin(t_cmds *cmds);
void	check_builtins(t_cmds *cmds);

/* STD MANAGEMENT */

void	save_stdout(t_main *shell);
void	save_stdin(t_main *shell);
void	restore_stdout(t_main *shell);
void	restore_stdin(t_main *shell, int redirected_fd);

/* REDIR */
void	redir_builtin(t_cmds *cmds, t_main *shell, t_stds *fd_stds);
int		redirect_output_builtin(t_files *outfile, t_main *shell);
int		redirect_input_builtin(t_files *infile, t_main *shell);

/* REDIRECTION_UTILS */

void	handle_redirection(t_cmds *cmd);

/*----------------------------PLUMBING UTILS SUBDIR--------------------------*/

/* PLUMBING 1 */

void	close_middle_parent(int fds[2], int fd_in);
void	close_middle_child(int fds[2], int fd_in);
void	close_first_parent(int fds[2]);
void	close_first_child(int fds[2]);

/* PLUMBING 2 */

void	close_fdin_last_child(int fd_in);
void	close_fdin_last_parent(int fd_in);
void	close_fdin_builtin(int fd_in);

/*----------------------------------UTILS DIR--------------------------------*/

/* CMDS_UTILS */

int		cmd_size(t_cmds *cmds);

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

/*----------------------------------EXECUTION-------------------------------*/

extern int	g_signal_received;

#endif
