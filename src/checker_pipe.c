/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:06:27 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/11 20:09:56 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	checker_pipe(char **argv, int argc)
{
	int	infile_fd;
	int	i;

	infile_fd = open(argv[0], O_CREAT | O_EXCL | O_WRONLY, 0600);
	i = 1;
	while (i < argc)
	{

		i++;
	}
}