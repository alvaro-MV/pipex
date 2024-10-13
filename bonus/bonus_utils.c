#include "../include/pipex_bonus.h"

int	*set_pipefds(t_pipe *pipex, int n_pipes)
{
	int	i;
	int	*pipefds;
	int	*next_pipe;

	i = 0;
	pipefds = (int *) malloc(sizeof(int) * 2 * n_pipes);
	if (pipefds == NULL)
		return (NULL);
	while (i < n_pipes)
	{
		next_pipe = pipefds + (2 * i);
		manage_pipe(next_pipe, pipex->path);
		i++;
	}
	return (pipefds);
}

void	close_pipefds(t_pipe *pipex, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		close(pipex->pipefds[2 * i]);
		close(pipex->pipefds[2 * i + 1]);
		i++;
	}
}

void	get_infile_hd(t_pipe *pipex)
{
	pipex->infile = here_doc(pipex->argv[0], pipex->path);
	if (pipex->infile == -1)
		ft_printf("%s: No such file or directory\n", pipex->argv[0]);
}

void	get_infile_pipex(t_pipe *pipex)
{
	pipex->infile = open(pipex->argv[0], O_RDONLY);
	if (pipex->infile == -1)
		ft_printf("%s: No such file or directory\n", pipex->argv[0]);
}