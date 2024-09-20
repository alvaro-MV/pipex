/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:58:19 by alvmoral          #+#    #+#             */
/*   Updated: 2024/09/20 18:56:30 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
	{
		write(fd, "(null)", 7);
		return ;
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// int	main()
// {
// 	char	s[] = "Hola";
// 	int	fd;

// 	fd = open("pp.txt", O_WRONLY | O_APPEND);
// 	ft_putstr_fd(s, fd);
// }
