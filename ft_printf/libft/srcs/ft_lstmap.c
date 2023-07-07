/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:28:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/18 21:13:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*mylist;
	t_list		*myliststart;

	(void) del;
	if (!lst || !f || !del)
		return (0);
	mylist = ft_lstnew((*f)(lst->content));
	if (!mylist)
		return (0);
	myliststart = mylist;
	while (lst->next)
	{
		lst = lst->next;
		mylist->next = ft_lstnew((*f)(lst->content));
		mylist = mylist->next;
		if (!mylist)
		{
			ft_lstclear(&myliststart, del);
			return (0);
		}
	}
	return (myliststart);
}
