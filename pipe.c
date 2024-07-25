/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:43:14 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/25 19:14:19 by alvaro           ###   ########.fr       */
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

void    exec_command(char **path, char **command)
{
    if (command == NULL)
        (perror("Memory allocation problem\n"), exit(-1));
    command[0] = find_exec_in_PATH(path, command[0]);
    if (command[0] == NULL)
        (perror("Executable not found\n"), exit(-1));
    execve(command[0], command, NULL);
    (perror("Execution error\n"), exit(-1));
}

int get_fd(char **argv, int pipefd[2])
{
    int io_file_fd;
    close(pipefd[0]);

//    if (argv[1]  NULL)
    //{
        //argv++;
        //return (pipefd[1]);
    //}
//    else
        //io_file_fd = open(argv[0], O_WRONLY);
    io_file_fd = pipefd[1];
    return (io_file_fd);
}

char    **get_next_command(char *command_char)
{
    char    **next_command;

    next_command = ft_split(command_char, ' ');
    if (next_command == NULL)
        return (NULL);
    return (next_command);
}

void    execute_pipe(char **path, char **argv)
{
    int     ret;
    int     status;
    int     pipefd[2];
    int     io_file_fd;
    char    **command;

    manage_pipe(pipefd);
    io_file_fd = open(argv[0], O_RDONLY);
    manage_dup2(io_file_fd, 0);
    close(io_file_fd);
    (command = NULL, argv++);
    while (argv[2] != NULL)
    {
        ft_printf("volver: %s fd_0: %d fd_1: %d\n", *argv, pipefd[0], pipefd[1]); //testeo
        ret = fork();
        wait(&status);
        if (ret == 0)
        {
            command = get_next_command(*argv);
            manage_dup2(pipefd[1], 1);
            close(pipefd[1]);
            //io_file_fd = get_fd(argv, pipefd);
            exec_command(path, command);
        }
        manage_status(status);
        argv++;
        ft_printf("volver: %s fd_0: %d fd_1: %d\n", *argv, pipefd[0], pipefd[1]); //testeo
        manage_dup2(pipefd[0], 0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
}
