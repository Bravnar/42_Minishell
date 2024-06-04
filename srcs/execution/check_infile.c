#include "minishell.h"


int	check_infile(char *infile, t_main *shell)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		if (access(infile, F_OK) == 0)
			shell->err_code = PERM_DENIED;
		else
			shell->err_code = NO_INFILE;
		return (EXIT_FAILURE);
	}
	return (fd);
}

int	check_infiles(t_main *shell, t_cmds *cmds)
{
	t_cmds	*temp;
	t_files	*tmp_file;

	temp = cmds;
	while (temp)
	{
		tmp_file = temp->files;
		while (tmp_file)
		{
			if (tmp_file->type == INFILE)
			{
				if (check_infile(tmp_file->file_name, shell))
					return (error_handler(shell->err_code,
							tmp_file->file_name), EXIT_FAILURE);
			}
			tmp_file = tmp_file->next;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
