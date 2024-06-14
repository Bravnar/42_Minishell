#include "minishell.h"

void	redirect_output(t_files *outfile, t_main *shell)
{
	int	fd;

	if (outfile->type == OUTFILE)
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror("Failed to open output file");
	if (dup2(fd, shell->out) == -1)
	{
		ft_fprintf(shell->err, "dup2\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	redirect_input(t_files *infile)
{
	int	fd;

	fd = open(infile->file_name, O_RDONLY);
	if (fd == -1)
		perror("Failed to open input file");
	return (fd);
}
