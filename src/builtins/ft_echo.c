/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:37 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 10:24:08 by rrakotos         ###   ########.fr       */
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

int	ft_echo(t_tokens *tokens)
{
	int		option;
	t_arg	*argt;

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
			ft_putstr_fd(argt->arg_str, STDOUT_FILENO);
			break ;
		}
		ft_putstr_fd(argt->arg_str, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		argt = argt->next_arg;
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
