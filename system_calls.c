/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:59:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/08/20 18:11:08 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_calls.h"

int	manage_pipe(int pipefd[2], char **path)
{
	if (pipe(pipefd) == -1)
	{
		perror("Pipe not working\n");
		ft_free_array(path);
		exit(-1);

	}
	return (0);
}

void	manage_dup2(int old_fd, int new_fd, char **path)
{
	int	dup_value;

	if (old_fd == -1)
	{
		perror("Bad file descriptor");
		ft_free_array(path);
		exit(-1);
	}
	else
		dup_value = dup2(old_fd, new_fd);
	if (dup_value == -1)
		(perror("Not posible to duplicate infile fd\n"), exit(-1));
}

int	ffork(char  **path)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		(perror("fork error\n"), exit(-1));
		ft_free_array(path);
		exit(-1);
	}
	return (ret);
}

int	manage_status(int status, char **path)
{
	if (status == -1)
	{
		perror("Execution error\n");
		ft_free_array(path);
		exit(-1);
	}
	return (0);
}

