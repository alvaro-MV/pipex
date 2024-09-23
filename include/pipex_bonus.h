/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:04:38 by alvaro            #+#    #+#             */
/*   Updated: 2024/09/23 10:04:39 by alvaro           ###   ########.fr       */
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

char	**get_path(char *env[]);
void	checker_args(char **argv, int argc, char **path);

int		exec_exist(char **path, char *exec);
void	bad_exec(int pipefd[2], char **argument, char **argv, char **path);
char	*find_exec_in_path(char **path, char *exec);
void	execute_child(char **argv, char **path, int pipefd[2]);
void	execute_pipe(char **path, char **argv, int infd);

// get next line

char	*get_next_line(int fd);

#endif