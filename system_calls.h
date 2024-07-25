/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:22:07 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/25 16:35:52 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_CALLS_H
# define SYSTEM_CALLS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "lib/include/libft.h"

int	manage_pipe(int pipefd[2]);
int	manage_dup2(int old_fd, int new_fd);
int	manage_fork_ret(int ret);
int	manage_status(int status);

#endif