/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:47 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/21 17:38:36 by rrakotos         ###   ########.fr       */
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

static long long	ft_atoll(const char *nptr)
{
	int			neg;
	long long	i;
	long long	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		neg = neg * -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (10 * nb) + (nptr[i] - '0');
		i++;
	}
	return (nb * neg);
}

int	ft_exit(t_tokens *tokens)
{
	int		exit_code;
	int		len_arg;
	char	*str_arg;

	exit_code = 0;
	len_arg = count_arg(tokens->token_arg);
	printf("exit\n");
	if (len_arg > 0)
		str_arg = tokens->token_arg->arg_str;
	if (len_arg > 0 && is_numeric(str_arg))
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	else if (len_arg == 1 && is_numeric(str_arg))
	{
		if (LLONG_MAX > ft_atoll(str_arg))
		{
			printf("exit: %s: numeric argument required\n", str_arg);
			// ts aiko oe mi-exit inon ty
			exit(2);
			return (2);
		}
		exit_code = ft_atoi(str_arg);
		exit(exit_code % 256);
	}
	else if (len_arg > 0 && !is_numeric(str_arg))
	{
		printf("exit: %s: numeric argument required\n", str_arg);
		// ts aiko oe mi-exit inon ty
		exit(2);
		return (2);
	}
	exit(exit_code);
}
