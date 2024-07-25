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

void	execute_child(char **argv, char **path, int pipefd[2])
{
	char	**arguments;

	arguments = ft_split(*argv, ' ');
	arguments[0] = find_exec_in_PATH(path, arguments[0]);
	if (argv[2] != NULL)
	{
		if (dup2(pipefd[1], 1) == -1)
			(perror("dup"), exit(-1));
	}
	else
	{	
		int	file_fd = open(argv[1], O_RDWR, O_CREAT, O_TRUNC);
		manage_dup2(file_fd, 1);
		close(file_fd);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	execve(arguments[0], arguments, NULL);
	(perror("execve"), exit(-1));
}

void	execute_pipe(char **path, char **argv)
{
	int		pipefd[2];
	int		ret;
	int 	status;
	int		fdd;

	int	file_fd = open(*argv, O_RDONLY);
	manage_dup2(file_fd, 0);
	close(file_fd);
	argv++;	
	while (argv[1] != NULL)
	{
		if (pipe(pipefd) == -1)
			(perror("pipex"), exit(-1));
		ret = fork();
        manage_fork_ret(ret);
		if (ret == 0)
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
