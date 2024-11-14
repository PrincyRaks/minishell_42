/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:59:16 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 14:22:26 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_token(void)
{
	t_tokens	*instr;

	instr = malloc(sizeof(t_tokens));
	if (!instr)
		return (NULL);
	// cmd
	instr->token_cmd = NULL;
	// arguments
	instr->token_arg = NULL;
	instr->next = NULL;
	return (instr);
}

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
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
