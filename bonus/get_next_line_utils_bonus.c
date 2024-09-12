/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:09 by alvaro            #+#    #+#             */
/*   Updated: 2024/09/11 13:21:32 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strchr_g(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	c = (char) c;
	while (*s)
	{
		if (*s == c)
			return ((char *) s + 1);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	else
		return (0);
}

void	ft_lstadd_front_g(t_list_g **lst, char *content)
{
	t_list_g	*list;
	t_list_g	*new_n;

	if (!content)
		return ;
	new_n = (t_list_g *) malloc(sizeof(t_list_g));
	if (new_n == NULL)
		return ;
	new_n->content = content;
	list = *lst;
	new_n->next = list;
	*lst = new_n;
}

void	ft_lstadd_back_g(t_list_g **lst, char *content)
{
	t_list_g	*list;
	t_list_g	*holder;
	t_list_g	*new_n;

	new_n = (t_list_g *) malloc(sizeof(t_list_g));
	if (new_n == NULL || !content)
	{
		ft_lstclear_g(lst);
		return ;
	}
	new_n->content = content;
	new_n->next = NULL;
	list = *lst;
	if (list == NULL)
		*lst = new_n;
	if (list != NULL)
	{
		while (list != NULL)
		{
			holder = list;
			list = list->next;
		}
		holder->next = new_n;
	}
}

void	ft_lstclear_g(t_list_g **lst)
{
	t_list_g	*holder;
	t_list_g	*list;

	if (lst)
	{
		list = *lst;
		while (list != NULL)
		{
			holder = list;
			list = list->next;
			free(holder->content);
			free(holder);
		}
	}
}

int	ft_lstsize_g(t_list_g *lst)
{
	int	contador;

	contador = 0;
	while (lst != NULL)
	{
		contador++;
		lst = lst->next;
	}
	return (contador);
}
