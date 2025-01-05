/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:37 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/24 13:07:44 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	str += (*str == '-');
	if (*str == '\0')
		return (0);
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
	option = 0;
	argt = tokens->token_arg;
	while (argt != NULL && argt->arg_str != NULL && check_option(argt->arg_str))
	{
		option = 1;
		argt = argt->next_arg;
	}
	while (argt != NULL && argt->arg_str != NULL)
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
