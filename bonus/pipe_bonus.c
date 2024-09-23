/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:43:14 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/25 21:29:37alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*find_exec_in_path(char **path, char *exec)
{
	int		l_exec;
	int		l_path;
	char	pathname[PATH_MAX];

	if (access(exec, X_OK) == 0)
		return (ft_strdup(exec));
	if (exec[0] == '/')
		return (NULL);
	l_exec = ft_strlen(exec);
	l_path = 0;
	if (path != NULL)
	{
		while (*path != NULL)
		{
			l_path = ft_strlen(*path);
			ft_strlcpy(pathname, *path, l_path + 2);
			if (pathname[l_path - 1] != '/')
				ft_strlcat(pathname, "/", l_path + 2);
			ft_strlcat(pathname, exec, l_exec + l_path + 2);
			if (access(pathname, X_OK) == 0)
				return (free(exec), ft_strdup(pathname));
			path++;
		}
	}
	return (NULL);
}

void	bad_exec(int pipefd[2], char **arguments, char **argv, char **path)
{
	ft_putstr_fd(argv[0], 2);
	perror(": command not found.\n");
	close(pipefd[1]);
	close(pipefd[0]);
	ft_free_array(arguments);
	ft_free_array(path);
	exit(1); //Mirar codigos de error
}

/* 
	bad exec, mal orden, que el archivo de redireccion no exista, 
 */

void	execute_child(char **argv, char **path, int pipefd[2])
{
	char	**arguments;
	int		file_fd;

	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_path(path, arguments[0]);
	if (argv[2] != NULL)
		manage_dup2(pipefd[1], 1, path);
	else
	{
		file_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (perror(argv[1]), ft_free_array(path), exit (-1));
		manage_dup2(file_fd, 1, path);
		close(file_fd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	ft_free_array(path);
	if (arguments[0] == NULL)
		bad_exec(pipefd, arguments, argv, path);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe(char **path, char **argv, int infd)
{
	int		pipefd[2];
	int		status;
	int		fdd;

	fdd = 0;
	manage_dup2(infd, 0, path);
	close(infd);
	while (argv[1] != NULL)
	{
		manage_pipe(pipefd, path);
		if (ffork(path) == 0)
		{
			manage_dup2(fdd, 0, path);
			execute_child(argv, path, pipefd);
			free(*argv);
		}
		else
		{
			wait(&status);
			close(pipefd[1]);
			fdd = pipefd[0];
			++argv;
		}
	}
}
