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
			return(my_pwd(fd, shell, cmds->cmd_grp));
		else if (!ft_strcmp(cmds->cmd_grp[0], "exit"))
			return(my_exit(shell, cmds->cmd_grp));
	}
	return (EXIT_FAILURE);
}

int exec_single_builtin(t_cmds *cmds, t_main *shell)
{
	t_stds	fd_stds;

	fd_stds.in = -1;
	fd_stds.out = -1;
	redir_builtin(cmds, shell, &fd_stds);
	shell->err_code = builtins(cmds, shell, STDOUT_FILENO);
	if (cmds->last_outfile)
		restore_stdout(shell);
	if (cmds->last_infile)
		restore_stdin(shell, fd_stds.in);
	return (shell->err_code);
}

