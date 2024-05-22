#include "minishell.h"

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

void	builtins(t_cmds *cmds, t_main *shell)
{
	if (cmds && cmds->cmd_grp && cmds->cmd_grp[0])
	{
		//printf("current cmd_grp arg: %s\n", cmds->cmd_grp[0]);
		if (!ft_strcmp(cmds->cmd_grp[0], "cd"))
		{
			//printf("executing cd\n");
			cd(shell, cmds->cmd_grp);
		}
		else if (!ft_strcmp(cmds->cmd_grp[0], "env"))
			print_envp(&shell->env);
	}
}

void	my_rl_initialize(void)
{
	int	fd;
	int	saved_stdin;
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
	//int		count = 0;
	
	lex = shell->l;
	//while (count < 3)
	my_rl_initialize();
	while (1)
	{
		terminal_prompt(shell);
		//print_prompt_info(shell->prompt);
		lex->input = readline(shell->prompt);
		if (!lex->input)
			break ;
		if (lex->input[0])
			add_history(lex->input);
		lexer(lex, shell);
		builtins(shell->cmds, shell);
		free_all(shell);
		clear_t_cmds(shell);
		//count++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*shell;

	(void)	ac;
	(void)	av;
	shell = init_structs(envp);
	gameplay_loop(shell);
	free_main(shell);
}
