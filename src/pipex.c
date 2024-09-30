/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:50:50 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/21 19:07:02by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../lib/include/libft.h"

char	**get_path(char *env[])
{
	char	**path;
	char	*path_env;

	while (ft_strncmp(*env, "PATH", 4))
		env++;
	if (env == NULL)
		return (NULL);
	path_env = *env;
	path_env = &(path_env[5]);
	path = ft_split(path_env, ':');
	if (path == NULL)
		return (NULL);
	return (path);
}

static int	*set_pipefds(t_pipe *pipex, int n_pipes)
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

int	main(int argc, char *argv[], char *env[])
{
	t_pipe	pipex;

	argv++;
	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("<infile command 1 ... command n outfile>\n");
		return (1);
	}
	pipex.n_pipes = argc - 3;
	pipex.path = get_path(env);
	if (pipex.path == NULL)
		return (1);
	pipex.pipefds = set_pipefds(&pipex, argc - 3);
	if (pipex.pipefds == NULL)
		return (1);
	pipex.infile = open(argv[0], O_RDONLY);
	if (pipex.infile == -1)
		ft_printf("%s: No such file or directory\n", argv[0]);
	argv++;
	pipex.argv = argv;
	execute_pipe(&pipex);
	ft_free_array(pipex.path);
	return (0);
}
