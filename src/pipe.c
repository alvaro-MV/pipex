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

#include "../include/pipex.h"

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
	return (free(exec), NULL);
}

void	bad_exec(t_pipe *pipex, char **arguments)
{
	ft_putstr_fd(pipex->argv[0], 2);
	perror(": command not found.\n");
	close_pipefds(pipex, pipex->n_pipes);
	ft_free_array(arguments);
	ft_free_array(pipex->path);
	exit(1);
}

void	parent_wait(t_pipe *pipex, int cmd_idx)
{
	int		i;
	int		status;

	i = 0;
	while (i < cmd_idx)
		waitpid(pipex->pid[i++], &status, 0);
	free(pipex->pid);
	if (WIFEXITED(status))
		pipex->exit_status = WEXITSTATUS(status);
	else
		pipex->exit_status = 1;
}

/* 
	bad exec, mal orden, que el archivo de redireccion no exista, 
 */
void	execute_child(t_pipe *pipex, int cmd_idx)
{
	char	**arguments;
	int		out_fd;
	int		*pipe_pos;

	arguments = ft_split(*pipex->argv, ' ');
	arguments[0] = find_exec_in_path(pipex->path, arguments[0]);
	if (arguments[0] == NULL)
		bad_exec(pipex, arguments);
	pipe_pos = pipex->pipefds + (2 * cmd_idx);
	if (pipex->argv[2] != NULL)
		manage_dup2(*(pipe_pos + 1), 1, pipex->path);
	else
	{
		out_fd = open(pipex->argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
			return (perror(pipex->argv[1]), exit(-1));
		manage_dup2(out_fd, 1, pipex->path);
		close(out_fd);
	}
	close_pipefds(pipex, pipex->n_pipes);
	ft_free_array(pipex->path);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe(t_pipe *pipex)
{
	int 	cmd_idx;
	int		*pipe_pos;

	cmd_idx = 0;
	manage_dup2(pipex->infile, 0, pipex->path);
	close(pipex->infile);
	while (pipex->argv[1] != NULL)
	{
		pipex->pid[cmd_idx] = ffork(pipex->path);
		if (pipex->pid[cmd_idx] == 0)
		{
			pipe_pos = pipex->pipefds + (2 * cmd_idx);
			if (cmd_idx > 0)
				manage_dup2(*(pipe_pos - 2), 0, pipex->path);
			execute_child(pipex, cmd_idx);
			free(*(pipex->argv));
		}
		else
		{
			++pipex->argv;
			++cmd_idx;
		}
	}
	close_pipefds(pipex, pipex->n_pipes);
	parent_wait(pipex, cmd_idx);
}
