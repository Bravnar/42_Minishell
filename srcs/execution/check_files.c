#include "minishell.h"


int	check_infile(char *infile, t_main *shell)
{
	int	fd;

	fd = open(infile, O_RDONLY, 00644);
	if (fd == -1)
	{
		if (access(infile, F_OK) == 0)
			shell->err_code = PERM_DENIED;
		else
			shell->err_code = NO_INFILE;
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_outfile(char *outfile, t_main *shell, t_type t)
{
	int	fd;

	if (t == OUTFILE_APP)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
	{
		if (access(outfile, F_OK) == 0)
			shell->err_code = PERM_DENIED;
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_file(t_files *file, t_main *shell)
{
	if (file->type == INFILE)
	{
		if (check_infile(file->file_name, shell))
			return (EXIT_FAILURE);
	}
	else if (file->type == OUTFILE || file->type == OUTFILE_APP)
	{
		if (check_outfile(file->file_name, shell, file->type))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_files(t_main *shell, t_cmds *cmds)
{
	t_cmds	*temp;
	t_files	*tmp_file;

	temp = cmds;
	temp->last_infile = NULL;
	temp->last_outfile = NULL;
	while (temp)
	{
		tmp_file = temp->files;
		while (tmp_file)
		{
			if (check_file(tmp_file, shell))
				return (error_handler(shell->err_code,
						tmp_file->file_name), EXIT_FAILURE);
			if (tmp_file->type == INFILE)
				temp->last_infile = tmp_file;
			if (tmp_file->type == OUTFILE || tmp_file->type == OUTFILE_APP)
				temp->last_infile = tmp_file;
			tmp_file = tmp_file->next;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
