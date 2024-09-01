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

char	**get_path(char *env[])
{
	char	**path;
	char	*path_env;

	while (ft_strncmp(*env, "PATH", 4))
		env++;
	if (env == NULL)
		return (NULL);
	path_env = *env;
	path_env = &(path_env[5]);
	path = ft_split(path_env, ':');
	if (path == NULL)
		return (NULL);
	return (path);
}

void	call_pipe(char **path, char **argv)
{
	int	infile;

	infile = open(argv[0], O_RDONLY);
	if (infile == -1)
		return (perror("Bad file desciptor"));
	argv++;
	execute_pipe(path, argv, infile);
}

void	call_here_doc(char **path, char **argv)
{
	int	infile;

	infile = here_doc(argv[1], path);
	if (infile == -1)
		return (perror("Bad file desciptor"));
	execute_pipe_hd(path, &argv[2], infile);
}

int	start(int argc, char *argv[], char *env[])
{	
	char	**path;

	path = get_path(env);
	if (path == NULL)
		return (0);

	if (argc < 5)
	{
		ft_printf("Incorrect format: ");
		ft_printf("<infile command 1 ... command n outfile>\n");
		exit(1);
	}
	argv++;
	if (ft_strcmp(argv[0], "here_doc") != 0)
		call_pipe(path, argv);
	else
		call_here_doc(path, argv);	

	ft_free_array(path);
}

int	main(int argc, char *argv[], char *env[])
{
	start(argc, argv, env);

	return (0);
}
