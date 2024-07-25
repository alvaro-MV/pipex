#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	execute_child(char **argv, char **path, char **arguments, int pipefd[2])
{
	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_PATH(path, arguments[0]);
	ft_printf("primer arg: %s\n", arguments[0]);
	if (dup2(pipefd[1], 1) == -1)
		(perror("dup"), exit(-1));
	close(pipefd[1]);
	close(pipefd[0]);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

int	main(int argc, char **argv, char *env[])
{
	int		pipefd[2];
	int		ret;
	int 	status;
	char	**path;
	char	**arguments;
	int		fdd;


	path = get_PATH(env);
	argv++;	
//	if (dup2(pipefd[0], 0) == -1)
		//(perror("dup"), exit(-1));
	//close(pipefd[0]);
	//close(pipefd[1]);
	while (argv[1] != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipex");
			exit(-1);
		}
		ret = fork();
		if (ret == -1)
			(perror("fork"), exit(-1));
		else if (ret == 0)
		{
			dup2(fdd, 0);
			execute_child(argv, path, arguments, pipefd);
		}
		else
		{
			wait(&status);
			close(pipefd[1]);
			fdd = pipefd[0];
			++argv;
		}
	}
	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_PATH(path, arguments[0]);
	ft_printf("primer arg: %s\n", arguments[0]);
	//testeo
	int	idx = 0;
	while (arguments[idx])
	{
		ft_printf("arg: %s", arguments[idx]);
		idx++;
	}
	//testeo
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
	return (0);
}
