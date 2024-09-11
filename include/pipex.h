/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:44:12 by alvaro            #+#    #+#             */
/*   Updated: 2024/09/11 20:11:42 by alvmoral         ###   ########.fr       */
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
#include "../include/get_next_line.h"

char	**get_path(char *env[]);
void	call_pipe(char **path, char **argv, int argc);
void	call_here_doc(char **path, char **argv, int argc);

void	bad_exec(int pipefd[2], char **arguments, char **path);
char	*find_exec_in_path(char **path, char *exec);
void	execute_child(char **argv, char **path, int pipefd[2]);
void	execute_pipe(char **path, char **argv, int infd);

// get next line

char	*get_next_line(int fd);

int	start(int argc, char *argv[], char *env[]);
#endif