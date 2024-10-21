/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:26:14 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:30:29 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	head = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
