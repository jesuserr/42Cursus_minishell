/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:51:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/12 18:44:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_lstfindcontent(t_list *lst, int (*find)(void *, int), int tofind)
{
	while (lst)
	{
		if (find(lst->content, tofind))
			return (lst->content);
		lst = lst->next;
	}
	return (0);
}

void	*ft_lstfindlst(t_list *lst, int (*find)(void *, int), int tofind)
{
	while (lst)
	{
		if (find(lst->content, tofind))
			return (lst);
		lst = lst->next;
	}
	return (0);
}
