#include "lib/include/libft.h"
# include <linux/limits.h>

char	*find_exec_in_path(char **path, char *exec)
{
	int		l_exec;
	int		l_path;
	char	pathname[PATH_MAX];

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

int	main(int argc, char *argv[], char *env[])
{
	char **path = get_path(env);
	char *exec = find_exec_in_path(path, "oiandsfobndifnoefg");
	if (exec != NULL)
	{
		ft_printf("exec: %s\n", exec);
		free(exec);
	}
	ft_free_array(path);
}
