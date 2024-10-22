/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:50:50 by alvaro            #+#    #+#             */
/*   Updated: 2024/10/22 12:07:48 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../lib/include/libft.h"
#include "../include/system_calls.h"

char	**get_path(char *env[])
{
	char	**path;
	char	*path_env;

	if (env == NULL)
		return (NULL);
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	if (*env == NULL)
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

int	init_pipex(t_pipe *pipex, int argc, char **env)
{
	pipex->n_pipes = argc - 3;
	pipex->path = get_path(env);
	pipex->pid = (pid_t *) ft_calloc((pipex->n_pipes), sizeof(pid_t));
	if (pipex->pid == NULL)
		return (ft_free_array(pipex->path), 1);
	pipex->pipefds = set_pipefds(pipex, argc - 3);
	if (pipex->pipefds == NULL)
		return (ft_free_array(pipex->path), free(pipex->pid), 1);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipe	pipex;

	if (argc != 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("<infile command 1 ... command n outfile>\n");
		return (1);
	}
	argv++;
	pipex.argv = argv;
	if (init_pipex(&pipex, argc, env))
		return (1);
	pipex.infile = open(argv[0], O_RDONLY);
	if (pipex.infile == -1)
		perror(argv[0]);
	pipex.outfile = open(pipex.argv[argc - 2], O_RDWR, O_CREAT, O_TRUNC, 0644);
	if (pipex.outfile == -1)
		return (perror(" "), free_pipex(&pipex), -1);
	pipex.argv = argv + 1;
	execute_pipe(&pipex);
	manage_close(pipex.outfile);
	ft_free_array(pipex.path);
	return (pipex.exit_status);
}
