/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:43:14 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/25 21:29:37alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_exec_in_PATH(char **path, char *exec)
{
    int     l_exec;
    int     l_path;
    char    pathname[PATH_MAX];

    if (access(exec, X_OK) == 0)
        return (ft_strdup(exec));
    if (exec[0] == '/')
        return (NULL);
    l_exec = ft_strlen(exec);
    l_path = 0;
    if (path != NULL) 
    {
        while (*path != NULL)
        {
            l_path = ft_strlen(*path);
            ft_strlcpy(pathname, *path, l_path + 2);
            if (pathname[l_path - 1] != '/')
                ft_strlcat(pathname, "/", l_path + 2);
            ft_strlcat(pathname, exec, l_exec + l_path + 2);
            if (access(pathname, X_OK) == 0)
                return (ft_strdup(pathname));
            path++;
        }
    }
    return (NULL);
}
void	bad_exec(int pipefd[2], char **arguments)
{
	char	*freed_ptr;
	close(pipefd[1]);
	close(pipefd[0]);
	while (*arguments)
	{
		freed_ptr = *arguments;
		free(freed_ptr);
		arguments++;
	}
	perror("Bad executable");
	exit(-1);
}

/* 
	bad exec, mal orden, que el archivo de redireccion no exista, 
 */

void	execute_child(char **argv, char **path, int pipefd[2])
{
	char	**arguments;
	int		file_fd;

	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_PATH(path, arguments[0]);
	if (arguments[0] == NULL)
		bad_exec(pipefd, arguments);
	if (argv[2] != NULL)
	{
		if (dup2(pipefd[1], 1) == -1)
			(perror("dup"), exit(-1));
	}
	else
	{	
		file_fd = open(argv[1], PIPE_MASK);
		manage_dup2(file_fd, 1);
		close(file_fd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe(char **path, char **argv, int infd)
{
	int		pipefd[2];
	int		status;
	int		fdd;

	manage_dup2(infd, 0);
	close(infd);
	while (argv[1] != NULL)
	{
		manage_pipe(pipefd);
		if (Fork() == 0)
		{
			dup2(fdd, 0);
			execute_child(argv, path, pipefd);
		}
		else
		{
			wait(&status);
			close(pipefd[1]);
			fdd = pipefd[0];
			++argv;
		}
	}
}
