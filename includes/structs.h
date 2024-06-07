#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	NONE,
	CMD,
	ARG,
	INFILE,
	OUTFILE,
	OUTFILE_APP,
	REDIR_IN,
	REDIR_OUT,
	PIPE_SYMBOL,
	APPEND,
	HEREDOC,
	HEREDOC_END,
	CMD_FULL,
}	t_type;

typedef enum e_err
{
	NO_ERR,
	BAD_QUOTES,
	BAD_REDIRS,
	BAD_PIPES,
	BAD_REDIRS_NL,
	MANY_ARGS,
	NO_INFILE,
	PERM_DENIED
}	t_err;

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				printable;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_counts
{
	int				count_in_files;
	int				count_out_files;
	int				count_cmds;
	int				count_pipes;
}	t_counts;

typedef struct s_llex
{
	char			*value;
	char			is_in_quotes;
	int				index;
	int				needs_exp;
	int				conn_with_prev;
	char			*exp_tmp;
	t_type			type;
	struct s_llex	*next;
	struct s_llex	*prev;
}	t_llex;

typedef struct s_lex
{
	int				i;
	int				j;
	int				s_quotes;
	int				d_quotes;
	int				s_count;
	int				d_count;
	char			q_char;
	int				backslash;
	int				token_len;
	int				word_len;
	char			*input;
	char			*trim;
	char			*token;
	int				err_code;
	t_llex			*link;
}	t_lex;

typedef struct s_files
{
	char			*file_name;
	t_type			type;
	struct s_files	*next;
	struct s_files	*prev;
}	t_files;

typedef struct s_cmds
{
	char			**cmd_grp;
	t_files			*files;
	int				is_heredoc;
	int				is_append;
	int				is_builtin;
	int				index;
	char			*path;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_main
{
	int				ac;
	char			**av;
	char			**envp;
	char			*prompt;
	char			*username;
	int				has_env;
	t_err			err_code;
	t_lex			*l;
	t_cmds			*cmds;
	t_envp			*env;
	t_counts		*counts;
}	t_main;

#endif
