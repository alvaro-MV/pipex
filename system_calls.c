#include "system_calls.h"

int	manage_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
		(perror("Pipe not working\n"), exit(-1));
	return (0);
}

void	manage_dup2(int old_fd, int new_fd)
{
	int	dup_value;
	if (old_fd != -1)
		dup_value = dup2(old_fd, new_fd);
    if (dup_value == -1)
        (perror("Not posible to duplicate infile fd\n"), exit(-1));
}

int	Fork()
{
	int	ret;

	ret = fork();
	if (ret == -1)
		(perror("fork error\n"), exit(-1));
	return (ret);
}

int	manage_status(int status)
{
	if (status == -1)
		perror("Execution error\n"), exit(-1);
	return (0);
}

