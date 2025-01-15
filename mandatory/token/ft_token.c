/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:59:16 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 15:59:28 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_token(void)
{
	t_tokens	*instr;

	instr = malloc(sizeof(t_tokens));
	if (!instr)
		return (NULL);
	instr->token_cmd = NULL;
	instr->token_arg = NULL;
	instr->token_flow = NULL;
	instr->errnum = DEFAULT;
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

void	clean_tokens(t_tokens **lst)
{
	t_tokens	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		clean_cmd((*lst)->token_cmd);
		clean_args(&(*lst)->token_arg);
		clean_flows(&(*lst)->token_flow);
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}
