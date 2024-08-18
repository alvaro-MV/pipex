/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:49:00 by alvaro            #+#    #+#             */
/*   Updated: 2024/08/18 21:58:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "lib/include/get_next_line.h"
#include "lib/include/libft.h"

void	execute_child_hd(char **argv, char **path, int pipefd[2])
{
	char	**arguments;
	int		file_fd;

	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_PATH(path, arguments[0]);
	if (arguments[0] == NULL)
		bad_exec(pipefd, arguments);
	if (argv[2] != NULL)
	{
		if (dup2(pipefd[1], 1) == -1)
			(perror("dup"), exit(-1));
	}
	else
	{	
		file_fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		manage_dup2(file_fd, 1);
		close(file_fd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe_hd(char **path, char **argv, int infd)
{
	int		pipefd[2];
	int		status;
	int		fdd;

	manage_dup2(infd, 0);
	close(infd);
	while (argv[1] != NULL)
	{
		manage_pipe(pipefd);
		if (Fork() == 0)
		{
			dup2(fdd, 0);
			execute_child(argv, path, pipefd);
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

int	here_doc(char *delimiter)
{
	char	*next_line;
	int		infd[2];

	manage_pipe(infd);
    if (delimiter[ft_strlen(delimiter)-1] != '\n')
    {
        delimiter = ft_strjoin(delimiter, "\n");
    }
	while (1)
	{
		next_line = get_next_line(0);
        if (ft_strcmp(next_line, delimiter) == 0)
			break ;
		write(infd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
    free(delimiter);
	close(infd[1]);
	return (infd[0]);
}
