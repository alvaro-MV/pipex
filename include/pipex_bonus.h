/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:04:38 by alvaro            #+#    #+#             */
/*   Updated: 2024/10/16 13:10:04 by alvaro           ###   ########.fr       */
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
	int		outfile;
	int		n_pipes;
	int		*pipefds;
	int		exit_status;
	pid_t	*pid;
}			t_pipe;

char	**get_path(char *env[]);
void	checker_args(char **argv, int argc, char **path);

int		exec_exist(char **path, char *exec);
char	*find_exec_in_path(char **path, char *exec);
void	execute_child(t_pipe *pipex, int cmd_idx);
void	execute_pipe(t_pipe *pipex);
void	close_pipefds(t_pipe *pipex, int n_pipes);
int		*set_pipefds(t_pipe *pipex, int n_pipes);
void	close_pipefds(t_pipe *pipex, int n_pipes);
void	get_infile(t_pipe *pipex);
void	free_pipex(t_pipe *pipex);

// get next line

char	*get_next_line(int fd);

#endif