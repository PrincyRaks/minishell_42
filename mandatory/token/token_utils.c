/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:33:25 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/12 15:20:32 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*last_token(t_tokens *token)
{
	while (token)
	{
		if (!token->next)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	addback_token(t_tokens **first_token, t_tokens *token)
{
	t_tokens	*end;

	if (first_token)
	{
		if (!*first_token)
			*first_token = token;
		else
		{
			end = last_token(*first_token);
			if (end)
				end->next = token;
		}
	}
}

int	count_token(t_tokens *lst)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}