/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:50:50 by alvaro            #+#    #+#             */
/*   Updated: 2024/10/22 12:13:36 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/heredoc.h"
#include "../lib/include/libft.h"

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

void	call_pipe(t_pipe *pipex, int argc)
{
	char	*out_name;

	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("<infile command 1 ... command n outfile>\n");
		close_pipefds(pipex, pipex->n_pipes);
		free(pipex->pid);
		return ;
	}
	out_name = pipex->argv[argc - 3];
	pipex->outfile = open(out_name, O_WRONLY, O_CREAT, O_TRUNC, 0644);
	if (pipex->outfile == -1)
		return (perror("outfile"), free_pipex(pipex), exit (-1));
	execute_pipe(pipex);
}

void	call_here_doc(t_pipe *pipex, int argc)
{
	char	*out_name;

	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("./pipex here_doc DEL command 1 command 2 outfile>\n");
		close_pipefds(pipex, pipex->n_pipes);
		free(pipex->pid);
		return ;
	}
	out_name = pipex->argv[argc - 4];
	pipex->outfile = open(out_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile == -1)
		return (perror(" "), free_pipex(pipex), exit (-1));
	execute_pipe(pipex);
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

	argv++;
	pipex.argv = argv;
	pipex.pipefds = NULL;
	pipex.pid = NULL;
	get_infile(&pipex);
	pipex.argv++;
	if (init_pipex(&pipex, argc, env))
		return (1);
	if (ft_strcmp(argv[0], "here_doc") != 0)
		call_pipe(&pipex, argc);
	else
		call_here_doc(&pipex, argc);	
	manage_close(pipex.outfile);
	ft_free_array(pipex.path);
	return (pipex.exit_status);
}
