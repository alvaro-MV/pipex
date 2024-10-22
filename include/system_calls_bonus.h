/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:55:01 by alvmoral          #+#    #+#             */
/*   Updated: 2024/10/22 19:55:02 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_CALLS_BONUS_H
# define SYSTEM_CALLS_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../lib/include/libft.h"

int		manage_pipe(int pipefd[2], char **path);
void	manage_dup2(int old_fd, int new_fd);
int		ffork(char **path);
int		manage_status(int status, char **path);
void	manage_close(int fd);

#endif