#include "include/pipex.h"
#include "lib/include/libft.h"



int	main(int argc, char *argv[], char *env[])
{
	int fd = open("", O_CREAT | O_EXCL | O_WRONLY, 0600);
	printf("ope fd: %d\n", fd);
	if (fd == -1)
		return (1);
}
