
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