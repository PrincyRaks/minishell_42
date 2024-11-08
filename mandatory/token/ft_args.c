/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:39:14 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:21 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addback_arg(t_arg **first_arg, char *str_arg)
{
	t_arg	arg;
	t_arg	*end;

	if (first_arg)
	{
		if (!*first_arg)
		{
			arg.arg_cmd = str_arg;
			arg.next_arg = NULL;
			*first_arg = arg;
		}
		else
		{
			end = last_arg(*first_arg);
			if (end)
				end->next_arg = arg;
		}
	}
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
