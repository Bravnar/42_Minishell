#include "minishell.h"

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

void	print_my_env(t_main	*shell)
{
	t_envp	*tmp;
	
	tmp = shell->env;
	printf("Printing env info: ------------------\n");
	while (tmp)
	{
		printf("%s :: %s\n", tmp->key, tmp->value);
		printf("printable state: %d\n", tmp->printable);
		tmp = tmp->next;
	}
	
}

void	print_my_shell(t_main	*shell)
{
	printf("Printing shell info: ------------------\n");
	printf("has_env: %d\n", shell->has_env);
	printf("fd_in: %d\n", shell->in);
	printf("fd_out: %d\n", shell->out);
	printf("fd_err: %d\n", shell->err);
}

/* Simple ft_strcmp to check builtins
   To "catch" the builtins before going
   to execution */
void	builtins(t_cmds *cmds, t_main *shell)
{
	if (cmds && cmds->cmd_grp && cmds->cmd_grp[0])
	{
		if (!ft_strcmp(cmds->cmd_grp[0], "cd"))
			cd_new(shell, cmds->cmd_grp);
		else if (!ft_strcmp(cmds->cmd_grp[0], "env"))
			print_envp(&shell->env);
		else if (!ft_strcmp(cmds->cmd_grp[0], "export"))
			export(shell, cmds->cmd_grp);
		else if (!ft_strcmp(cmds->cmd_grp[0], "echo"))
			my_echo(shell, cmds->cmd_grp);
		else if (!ft_strcmp(cmds->cmd_grp[0], "unset"))
			unset_env(cmds->cmd_grp, &shell->env);
		else if (!ft_strcmp(cmds->cmd_grp[0], "exit"))
			exit (1);
		else if (!ft_strcmp(cmds->cmd_grp[0], "my_env"))
			print_my_env(shell);
		else if (!ft_strcmp(cmds->cmd_grp[0], "my_shell"))
			print_my_shell(shell);
		else if (!ft_strcmp(cmds->cmd_grp[0], "pwd"))
			my_pwd(shell);
	}
}

/* Only used to trick the linux machines for correct compilation
   Uses an empty file to trick readline into executing once
   without user input */

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
		printf("%d\n", STDIN_FILENO);
	}
}

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;
	// int	count = 0;


	// count = 0;
	lex = shell->l;
	if (!APPLE)
		my_rl_initialize();
	// while (count < 3)
	while (1)
	{
		terminal_prompt(shell);
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		lexer(lex, shell);
		//parser_main() should be called here, for now is in lexer()
		builtins(shell->cmds, shell);
		// is_builtin(shell->cmds);
		execute(shell->cmds, shell);
		free_all(shell);
		clear_t_cmds(shell);
		// count++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;

	(void) ac;
	(void) av;
	shell = init_structs(envp);
	gameplay_loop(shell);
	free_main(shell);
}


/*
	TO DO:

	Stan:
	1) Refactor functions that need refactoring (handle redirs etc)
	2) Adapt the "glueing logic" for heredoc and append ✅
	3) Finilize the "expansion()" function to follow all steps correctly
		including the replace function from Hadri ✅
	4) Clean up all files and ensure norminette
	5) Finish implementation of builtins in MAIN and NOENV
	6) for heredoc END, change the logic of expansion (ffs)

	Hadrien:
	1) Continue execution
	2) See point 1)
 */
