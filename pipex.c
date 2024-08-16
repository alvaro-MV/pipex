/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:50:50 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/21 19:07:02by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "heredoc.h"
#include "lib/include/libft.h"

char    **get_PATH(char *env[])
{
    char    **path;
    char    *path_env;

    while(ft_strncmp(*env, "PATH", 4))
        env++;
    if (env == NULL)
        return (NULL);
    path_env = *env;
    path_env = &(path_env[5]);
    path = ft_split(path_env, ':');
    return (path);
}

void    call_pipe(char **path, char **argv)
{
    int infile;

    infile = open(argv[0], O_RDONLY);
    argv++;
    execute_pipe(path, argv, infile, PIPE_MASK);
}

void    call_here_doc(char **path, char **argv)
{
    int infile;

	infile = here_doc(argv[1]);
	execute_pipe(path, &argv[2], infile, HERE_MASK);
}

int main(int argc, char *argv[], char *env[])
{
    char    **path;

    if (argc < 5)
    {
        ft_printf("Incorrect format: ");
        ft_printf("<infile command 1 ... command n outfile>\n");
        return (0);
    }
    path = get_PATH(env);
    if (path == NULL)
        return (0);
    argv++;
    if (ft_strcmp(argv[0], "here_doc") != 0)
        call_pipe(path, argv);
    else
        call_here_doc(path, argv);
    while (*path != NULL)
    {
        free(*path);
        path++;
    }
    return (0);
}
