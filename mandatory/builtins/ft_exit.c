/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:47 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/11 14:23:39 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			return (1);
		}
		exit_code = ft_atoi(args[1]);
		if (args[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		exit(exit_code % 256);
	}
	exit(exit_code);
}
