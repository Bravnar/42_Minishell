#include "minishell.h"

int	builtins(t_cmds *cmds, t_main *shell, int fd)
{
	if (cmds && cmds->cmd_grp && cmds->cmd_grp[0])
	{
		if (!ft_strcmp(cmds->cmd_grp[0], "cd"))
			return(cd_new(shell, cmds->cmd_grp));
		else if (!ft_strcmp(cmds->cmd_grp[0], "env"))
			return(print_envp(&shell->env, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "export"))
			return(export(shell, cmds->cmd_grp, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "echo"))
			return(my_echo(cmds->cmd_grp, fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "unset"))
			return(unset_env(cmds->cmd_grp, &shell->env));
		else if (!ft_strcmp(cmds->cmd_grp[0], "pwd"))
			return(my_pwd(fd));
		else if (!ft_strcmp(cmds->cmd_grp[0], "exit"))
			return(my_exit(shell));
	}
	return (EXIT_FAILURE);
}

int exec_single_builtin(t_cmds *cmds, t_main *shell)
{
	int	fd_in;

	fd_in = -1;
	if (cmds->last_infile)
		fd_in = redirect_input_builtin(cmds->last_infile, shell);
	if (cmds->last_outfile)
		redirect_output_builtin(cmds->last_outfile, shell);
	shell->err_code = builtins(cmds, shell, STDOUT_FILENO);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (cmds->last_infile)
		restore_stdin(shell, fd_in);
	return (shell->err_code);
}

int exec_first_builtin(t_cmds *cmds, t_main *shell)
{
	int	fds[2];
	int fd_stds[2];

	save_stdout(shell);
	fd_stds[0] = -1;
	fd_stds[1] = -1;
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (cmds->last_infile)
		fd_stds[0] = redirect_input_builtin(cmds->last_infile, shell);
	if (cmds->last_outfile)
		fd_stds[1] = redirect_output_builtin(cmds->last_outfile, shell);
	builtins(cmds, shell, STDOUT_FILENO);
	close_first_parent(fds);
	if (cmds->last_infile)
		restore_stdin(shell, fd_stds[0]);
	if (cmds->last_outfile)
		restore_stdout(shell);
	else
	{
		if (dup2(shell->out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	return (fds[0]);
}
