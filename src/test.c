#include "../include/test.h"
#include <string.h>

static void test1() {
	int argc = 5;

	//Trying to execute this: 
	//	echo "Hola" | sed 's/$/, vete a la mierda/' | sed 's/$/. Vale, adios/'
	char *argv[6] = {
		"./pipex",
		"infile_test",
		"sed 's/$/, vete a la mierda/'",
		"sed 's/$/. Vale adios/'",
		"outfile_test",
		NULL,
	};

	char *env[1] = {
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/FireDaemon OpenSSL 3/bin/:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files/Git/cmd:/mnt/c/Program Files (x86)/Certbot/bin:/mnt/c/Python/Scripts/:/mnt/c/Python/:/mnt/c/Users/alvar/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/alvar/AppData/Local/Programs/Microsoft VS Code/bin"
	};

	int file_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(file_fd, "Hola", 5);
	close(file_fd);

	start(argc, argv, env);

	int outfile = open(argv[4], O_RDONLY);
	if (outfile == -1)
		return (perror("Outfile don't exist"));
	
	char buffer[64];
	read(outfile, buffer, 64);
	close(outfile);

	//Asertion part
	printf("%s", buffer);

	unlink(argv[1]);
	unlink(argv[4]);
}

int main() { 
	test1();
}