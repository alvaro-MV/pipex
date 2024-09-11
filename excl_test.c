#include <fcntl.h>

int	main(void)
{
	int fd = open("ou", O_CREAT | O_EXCL | O_WRONLY, 0600);
	printf("ope fd: %d\n", fd);
}
