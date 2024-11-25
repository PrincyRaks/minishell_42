/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:39:14 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/25 11:57:24 by rrakotos         ###   ########.fr       */
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
	arg->next_arg = NULL;
	return (arg);
}

static t_arg	*last_arg(t_arg *arg)
{
	while (arg)
	{
		if (!arg->next_arg)
			return (arg);
		arg = arg->next_arg;
	}
	return (NULL);
}

void	addback_arg(t_arg **first_arg, char *str_arg)
{
	t_arg	*arg;
	t_arg	*end;

	if (first_arg)
	{
		arg = new_arg();
		if (str_arg == NULL)
			arg->errnum = UNQUOTES;
		arg = new_arg();
		arg->arg_str = str_arg;
		if (!*first_arg)
			*first_arg = arg;
		else
		{
			end = last_arg(*first_arg);
			if (end)
				end->next_arg = arg;
		}
	}
}

void	clean_args(t_arg **lst)
{
	t_arg	*tmp;

	while (*lst != NULL)
	{
		free((*lst)->arg_str);
		tmp = (*lst)->next_arg;
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}
