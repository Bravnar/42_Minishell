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
			echo(shell, cmds->cmd_grp);
		else if (!ft_strcmp(cmds->cmd_grp[0], "exit"))
			exit (1);
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
	}
}

void	gameplay_loop(t_main *shell)
{
	t_lex	*lex;
	int		count;

	count = 0;
	lex = shell->l;
	if (!APPLE)
		my_rl_initialize();
	while (count < 5)
	{
		terminal_prompt(shell);
		lex->input = readline(shell->prompt);
		if (!lex->input)
			continue ;
		if (lex->input[0])
			add_history(lex->input);
		lexer(lex, shell);
		//parser_main() should be called here, for now is in lexer()
		builtins(shell->cmds, shell);
		//execute();
		free_all(shell);
		clear_t_cmds(shell);
		count++;
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
