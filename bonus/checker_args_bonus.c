/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:06:27 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/12 14:18:56by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exec_exist(char **path, char *exec)
{
	int		l_exec;
	int		l_path;
	char	pathname[PATH_MAX];

	if (access(exec, F_OK) == 0)
		return (1);
	if (exec[0] == '/')
		return (0);
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
				return (1);
			path++;
		}
	}
	return (0);
}

static	char	**get_arguments(char *raw_exec)
{
	char	**arguments;

	arguments = ft_split(raw_exec, ' ');
	if (arguments[0] == NULL)
		arguments[0] = "";
	return (arguments);
}

void	checker_args(char **argv, int argc, char **path)
{
	int		i;
	char	**arguments;

	i = 1;
	while (i < argc - 2)
	{
		arguments = get_arguments(argv[i]);
		if (!exec_exist(path, arguments[0]))
			ft_printf("%s: command not found.\n", arguments[0]);
		ft_free_array(arguments);
		i++;
	}
}
