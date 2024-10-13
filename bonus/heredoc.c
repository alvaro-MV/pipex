/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:22:49 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/20 18:48:07by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/heredoc.h"
#include "../lib/include/libft.h"
#include "../include/get_next_line.h"

int	here_doc(char *delimiter, char **path)
{
	char	*next_line;
	int		infd[2];

	manage_pipe(infd, path);
	if (delimiter[ft_strlen(delimiter)-1] != '\n')
	{
		delimiter = ft_strjoin(delimiter, "\n");
		if (delimiter == NULL)
			return (-1);
	}
	while (1)
	{
		ft_printf("> ");
		next_line = get_next_line(0);
		if (ft_strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break ;
		}
		write(infd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
	free(delimiter);
	close(infd[1]);
	return (infd[0]);
}
