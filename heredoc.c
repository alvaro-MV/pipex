/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:49:00 by alvaro            #+#    #+#             */
/*   Updated: 2024/08/16 19:27:59 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "lib/include/get_next_line.h"
#include "lib/include/libft.h"

int	here_doc(char *delimiter)
{
	char	*next_line;
	int		infd[2];

	manage_pipe(infd);
    if (delimiter[ft_strlen(delimiter)-1] != '\n')
    {
        delimiter = ft_strjoin(delimiter, "\n");
    }
	while (1)
	{
		next_line = get_next_line(0);
        if (ft_strcmp(next_line, delimiter) == 0)
			break ;
		write(infd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
    free(delimiter);
	close(infd[1]);
	return (infd[0]);
}
