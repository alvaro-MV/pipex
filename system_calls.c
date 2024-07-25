#include "system_calls.h"

int	manage_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
        (perror("Pipe not working\n"), exit(-1));
	return (0);
}

int	manage_dup2(int old_fd, int new_fd)
{
	int	dup_value;
	ft_printf("olllllllld: %d\n", old_fd);
	dup_value = dup2(old_fd, new_fd);
	ft_printf("dup_vla: %d\n", dup_value);
    if (dup_value == -1)
        (perror("Not posible to duplicate infile fd\n"), exit(-1));
}

int	manage_fork_ret(int ret)
{
	if (ret == -1)
		(perror("fork error\n"), exit(-1));
	return (0);
}

int	manage_status(int status)
{
	if (status == -1)
		perror("Execution error\n"), exit(-1);
	return (0);
}

