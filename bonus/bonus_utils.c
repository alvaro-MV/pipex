#include "../include/pipex_bonus.h"
#include "../include/heredoc.h"

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
		if (pipe(next_pipe) == -1)
		{
			ft_free_array(pipex->path);
			free(pipex->pid);
			exit(-1);
		}
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
	free(pipex->pipefds);
}

void	get_infile(t_pipe *pipex)
{
	if (ft_strcmp(pipex->argv[0], "here_doc") == 0)
	{
		pipex->infile = here_doc(pipex->argv[1], pipex->path);
		if (pipex->infile == -1)
			ft_printf("%s: No such file or directory\n", pipex->argv[0]);
		pipex->argv++;
	}
	else
	{
		pipex->infile = open(pipex->argv[0], O_RDONLY);
		if (pipex->infile == -1)
			ft_printf("%s: No such file or directory\n", pipex->argv[0]);
	}
}

void	free_pipex(t_pipe *pipex)
{
	ft_free_array(pipex->path);
	close_pipefds(pipex, pipex->n_pipes);
	free(pipex->pid);
}
