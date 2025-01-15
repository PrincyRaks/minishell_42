/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:39:14 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/30 18:15:49 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(t_arg *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next_arg;
	}
	return (i);
}

t_arg	*new_arg(void)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->arg_str = NULL;
	arg->errnum = DEFAULT;
	arg->operand = NOTOP;
	arg->next_arg = NULL;
	return (arg);
}

t_arg	*last_arg(t_arg *arg)
{
	while (arg)
	{
		if (!arg->next_arg)
			return (arg);
		arg = arg->next_arg;
	}
	return (NULL);
}

void	addback_arg(t_arg **first_arg, t_arg *node_arg)
{
	t_arg	*end;

	if (first_arg)
	{
		if (!*first_arg)
			*first_arg = node_arg;
		else
		{
			end = last_arg(*first_arg);
			if (end)
			{
				end->next_arg = node_arg;
				node_arg->next_arg = NULL;
			}
		}
	}
}

void	clean_args(t_arg **lst)
{
	t_arg	*tmp;

	while (*lst != NULL)
	{
		if ((*lst)->arg_str != NULL)
			free((*lst)->arg_str);
		tmp = (*lst)->next_arg;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
