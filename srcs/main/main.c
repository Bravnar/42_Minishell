#include "minishell.h"

int	g_signal_received = 0;
/* Gameplay loop free */
void	free_all(t_main *shell)
{
	if (shell->l->input)
	{
		free(shell->l->input);
		shell->l->input = NULL;
	}
	if (shell->l->trim)
	{
		free(shell->l->trim);
		shell->l->trim = NULL;
	}
	if (shell->l->link)
	{
		free_tokens(shell->l->link);
		shell->l->link = NULL;
	}
}

void	my_rl_initialize(void)
{
	int		fd;
	int		saved_stdin;
	char	*dummy;

	fd = open("dev/null.c", O_RDONLY, 777);
	if (fd != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		dummy = readline("");
		free(dummy);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		close(fd);
	}
}

void	receive_err(t_main *shell)
{
	char	*convert_status;
	int		err;
	int		reset;

	reset = 0;
	err = send_err_code(NULL);
	convert_status = NULL;
	if (err == 130 || err == 131)
	{
		convert_status = ft_itoa(err);
		set_env(&shell->env, "?", convert_status, 777);
		free(convert_status);
		send_err_code(&reset);
	}
}

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;

	lex = shell->l;

	// if (!APPLE)
	// 	my_rl_initialize();
	while (1)
	{
		g_signal_received = NORMAL;
		terminal_prompt(shell);
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		receive_err(shell);
		if (!lexer(lex, shell))
		{
			check_builtins(shell->cmds);
			execute(shell->cmds, shell);
		}
		free_all(shell);
		clear_t_cmds(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;

	(void) ac;
	(void) av;
	shell = init_structs(envp);
	signal_daddy(shell);
	gameplay_loop(shell);
	free_main(shell);
}


/*
	1) Error management file, refactor and add set_env $?, 777 --OK
	2) Fix signals Ctrl+C and Ctrl+\ ...
	3) Built-ins for piping and execution
	4) Norminette and headers
	5) Refactor and redistribute files where needed 
	6) Test that env -i works with no issue
	7) Test pipes
	8) Test redirs behaviour
	9) Test syntax errors + error handling
	10) Test many pipes
	11) Test mix of builtins and normals
	12) Play with environment and check behavior
	13) CHECK FOR LEAKS!
	14) Fucking signals, triple check
	15) Decide what to do with prompt issue with initialize?
	16) fix the export thing-a-majigy --OK
	17) fix exit arguments --OK
	18)  echo hello > abc | cat < abc
	19) unset PATH issue --OK
*/


/* void	handle_sigint(int sig)
{
	(void) sig;
	g_signal_received = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

if (g_signal_received)
		{
			g_signal_received = 0;
			free_all(shell);
			clear_t_cmds(shell);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}

 */
