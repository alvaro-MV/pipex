/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:59:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/10/22 12:14:33 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/system_calls.h"
#include "../include/pipex.h"

void	manage_dup2(int old_fd, int new_fd)
{
	int	dup_value;

	if (old_fd == -1)
		return ;
	dup_value = dup2(old_fd, new_fd);
	if (dup_value == -1)
		perror("");
}

int	ffork(char **path)
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

void	manage_close(int fd)
{
	if (fd != -1)
		close(fd);
}
