/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:25:47 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:25:49 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			end = ft_lstlast(*lst);
			if (end)
				end->next = new;
		}
	}
}
