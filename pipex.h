/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:44:12 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/25 18:56:44 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "lib/include/libft.h"
#include <fcntl.h>
#include <linux/limits.h>
#include "system_calls.h"

char    **get_PATH(char *env[]);
char    *find_exec_in_PATH(char **path, char *exec);
char    **get_next_command(char *command_char);
void    exec_command(char **path, char **command);
void    execute_pipe(char **path, char **argv);
int 	get_fd(char **argv, int pipefd[2]);

#endif