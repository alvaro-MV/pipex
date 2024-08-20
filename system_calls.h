/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:22:07 by alvaro            #+#    #+#             */
/*   Updated: 2024/08/20 18:11:53 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_CALLS_H
# define SYSTEM_CALLS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "lib/include/libft.h"

int		manage_pipe(int pipefd[2], char **path);
void	manage_dup2(int old_fd, int new_fd, char **path);
int		ffork(char **path);
int		manage_status(int status, char **path);

#endif