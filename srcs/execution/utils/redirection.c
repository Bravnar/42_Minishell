#include "minishell.h"

int	redirect_output(t_files *outfile, t_main *shell)
{
	int	fd;

	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(fd, shell->out) == -1)
	{
		ft_fprintf(shell->err, "dup2\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	redirect_input(t_files *infile)
{
	int	fd;

	fd = open(infile->file_name, O_RDONLY);
	return (fd);
}
