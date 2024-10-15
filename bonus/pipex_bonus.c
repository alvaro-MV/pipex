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

#include "../include/pipex_bonus.h"
#include "../include/heredoc.h"
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

void	call_pipe(t_pipe *pipex, int argc)
{
	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("<infile command 1 ... command n outfile>\n");
		return ;
	}
	//checker_args(argv, argc, path);
	pipex->outfile = open(pipex->argv[argc - 3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		return (perror(pipex->argv[argc - 3]), ft_free_array(pipex->path), exit(-1));
	execute_pipe(pipex);
}

void	call_here_doc(t_pipe *pipex, int argc)
{
	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("./pipex here_doc DEL command 1 command 2 outfile>\n");
		return ;
	}
	pipex->outfile = open(pipex->argv[argc - 4], O_APPEND | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		return (perror(pipex->argv[argc - 4]), ft_free_array(pipex->path), exit (-1));
	pipex->argv++;
	argc--;
	//checker_args(argv, argc, path);

	execute_pipe(pipex);
}

int	init_pipex(t_pipe *pipex, int argc, char **env)
{
	pipex->n_pipes = argc - 3;
	pipex->pid = (pid_t *) ft_calloc((pipex->n_pipes), sizeof(pid_t));
	if (pipex->pid == NULL)
		return (1);
	pipex->path = get_path(env);
	if (pipex->path == NULL)
		return (1);
	pipex->pipefds = set_pipefds(pipex, argc - 3);
	if (pipex->pipefds == NULL)
		return (1);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipe	pipex;

	argv++;
	pipex.argv = argv;
	get_infile(&pipex);
	pipex.argv++;
	if (init_pipex(&pipex, argc, env))
		return (1);
	if (ft_strcmp(pipex.argv[0], "here_doc") != 0)
		call_pipe(&pipex, argc);
	else
		call_here_doc(&pipex, argc);	
	ft_free_array(pipex.path);
	free(pipex.pipefds);
	return (pipex.exit_status);
}

