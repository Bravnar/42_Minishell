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
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(shell->err, "dup2\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	redirect_input(t_files *infile, t_main *shell)
{
	int	fd;

	fd = open(infile->file_name, O_RDONLY);

	if (fd == -1)
		perror("Failed to open input file");
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(shell->err, "dup2\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	redirect_stdin(int fd_in, t_main *shell)
{
	printf("Fd in: %d\n", fd_in);
	if (fd_in != -1)
	{
		if (dup2(STDIN_FILENO, fd_in) == -1)
		{
			ft_fprintf(shell->err, "dup2\n");
			return (EXIT_FAILURE);
		}
		printf("Closing fd in: %d\n", fd_in);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	return (0);
}
