/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:37 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/25 13:36:29 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	str += (*str == '-');
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	ft_echo(t_tokens *tokens)
{
	int		option;
	t_arg	*argt;

	// if (!tokens)
	//     return ;
	// handle echo $? / $VAR_ENV
	option = 0;
    argt = tokens->token_arg;
	while (argt != NULL && check_option(argt->arg_str))
	{
		option = 1;
		argt = argt->next_arg;
	}
	while (argt != NULL)
	{
		if (!argt->next_arg)
		{
			printf("%s", argt->arg_str);
			break ;
		}
		printf("%s ", argt->arg_str);
		argt = argt->next_arg;
	}
	if (!option)
		printf("\n");
}
