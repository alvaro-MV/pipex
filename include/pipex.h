/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:44:12 by alvaro            #+#    #+#             */
/*   Updated: 2024/09/25 10:04:26 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../lib/include/libft.h"
# include <fcntl.h>
# include <linux/limits.h>
# include "system_calls.h"
# include "../include/get_next_line.h"

typedef struct s_pipe
{
	char	**path;
	char	**argv;
	int		infile;
	int		n_pipes;
	int		*pipefds;
}			t_pipe;

char	**get_path(char *env[]);
void	checker_args(char **argv, int argc, char **path);

int		exec_exist(char **path, char *exec);
void	bad_exec(t_pipe *pipex, char **arguments);
char	*find_exec_in_path(char **path, char *exec);
void	execute_child(t_pipe *pipex, int cmd_idx);
void	execute_pipe(t_pipe *pipex);
void	close_pipefds(t_pipe *pipex, int n_pipes);

// get next line

char	*get_next_line(int fd);

#endif