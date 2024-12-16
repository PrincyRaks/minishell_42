/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:26:21 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/16 17:47:05 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_flow(t_flow *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next_flow;
	}
	return (i);
}

t_flow	*new_flow(void)
{
	t_flow	*flow;

	flow = malloc(sizeof(t_flow));
	if (!flow)
		return (NULL);
	flow->file = NULL;
	flow->operand = NOTOP;
	flow->next_flow = NULL;
	return (flow);
}

t_flow	*last_flow(t_flow *flows)
{
	while (flows)
	{
		if (!flows->next_flow)
			return (flows);
		flows = flows->next_flow;
	}
	return (NULL);
}

void	addback_flow(t_flow **first_flow, t_flow *node_flow)
{
	t_flow	*end;

	if (first_flow)
	{
		if (!*first_flow)
			*first_flow = node_flow;
		else
		{
			end = last_flow(*first_flow);
			if (end)
				end->next_flow = node_flow;
		}
	}
}

void	clean_flows(t_flow **lst)
{
	t_flow	*tmp;

	while (*lst != NULL)
	{
		free((*lst)->file);
		tmp = (*lst)->next_flow;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
