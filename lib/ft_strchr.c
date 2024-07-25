/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:04:11 by alvmoral          #+#    #+#             */
/*   Updated: 2024/04/06 14:58:25 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char) c;
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	else
		return (0);
}

// int main()
// {
//     const char s[] = "HOLLLa";
//     printf("str: %s\n", ft_strchr(s, 'O'));
//     printf("str: %s\n", strchr(s, 'O'));
// }
