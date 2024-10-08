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
	//int		i;
	int		*pipe_pos;
	pid_t	*pid;
	pid_t pollas; //Testeo

	cmd_idx = 0;
	pid = (pid_t *) malloc((pipex->n_pipes - 1) * sizeof(pid_t));
	manage_dup2(pipex->infile, 0, pipex->path);
	close(pipex->infile);
	while (pipex->argv[1] != NULL)
	{
		pid[cmd_idx] = ffork(pipex->path); //testeo
		if (pid[cmd_idx] == 0)
		{
			printf("child: %d\n", getpid());
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
	//i = 0;
	int	status;
	cmd_idx--;
//	while(cmd_idx > 0)
	//{
		//status = -13;
		//pollas = waitpid(-1, &status, WNOHANG);
		//ft_printf("ORING pollas: %d status: %d\n", pollas, WIFEXITED(status));
		//if (pollas == 0 && WIFEXITED(status))
		//{
			//pollas = waitpid(pid[cmd_idx], &status, 0);
			//ft_printf("pollas: %d\n", pollas);
		//}
		//else
			//ft_printf("pid i: %d --> ha terminado el puto proceso.\n", pid[cmd_idx]);
		//cmd_idx--;
		////i++;
	//}
	close_pipefds(pipex, pipex->n_pipes);
	while (cmd_idx >= 0)
	{
		pollas = waitpid(pid[cmd_idx], &status, 0);
		if (pollas == pid[1])
		{
			if ((cmd_idx == 1) && WIFEXITED(status))
				ft_printf("polassssssssssssss\n");
		}
		cmd_idx--;
	}
	ft_printf("FInallllll\n");
	free(pid);
}
