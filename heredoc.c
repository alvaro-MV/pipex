/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:49:00 by alvaro            #+#    #+#             */
/*   Updated: 2024/09/01 19:00:39ro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "lib/include/libft.h"

void	execute_child_hd(char **argv, char **path, int pipefd[2])
{
	char	**arguments;
	int		file_fd;

	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_path(path, arguments[0]);
	if (arguments[0] == NULL)
		bad_exec(pipefd, arguments, path);
	if (argv[2] != NULL)
		manage_dup2(pipefd[1], 1, path);
	else
	{
		file_fd = open(argv[1], O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (file_fd == -1)
			return (perror(argv[1]), ft_free_array(path), exit (-1));
		manage_dup2(file_fd, 1, path);
		//close(file_fd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	ft_free_array(path);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe_hd(char **path, char **argv, int infd)
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
			execute_child_hd(argv, path, pipefd);
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

int	here_doc(char *delimiter, char **path)
{
	char	*next_line;
	int		infd[2];

	manage_pipe(infd, path);
	if (delimiter[ft_strlen(delimiter)-1] != '\n')
	{
		delimiter = ft_strjoin(delimiter, "\n");
		if (delimiter == NULL)
			return (-1);
	}
	while (1)
	{
		next_line = get_next_line(0);
		if (ft_strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break ;
		}
		write(infd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
	free(delimiter);
	close(infd[1]);
	return (infd[0]);
}
