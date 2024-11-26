/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:47 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 18:17:44 by rrakotos         ###   ########.fr       */
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

static int	check_range(const char *str, long long *res)
{
	int	i;
	int	negative;

	negative = str[0] == '-';
	i = str[0] == '-' || str[0] == '+';
	while (str[i] != '\0')
	{
		if (*res > 922337203685477580)
			return (*res = 0);
		else if (!negative && *res == 922337203685477580 && (str[i] - '0')
			% 10 > 7)
			return (*res = 0);
		else if (negative && *res == 922337203685477580 && (str[i] - '0')
			% 10 > 8)
			return (*res = 0);
		*res = *res * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	ft_exit(t_tokens *tokens)
{
	int			len_arg;
	char		*str_arg;
	long long	exit_code;
	int			is_digit;

	exit_code = 0;
	str_arg = NULL;
	is_digit = is_numeric(str_arg);
	printf("exit\n");
	len_arg = count_arg(tokens->token_arg);
	if (len_arg > 0)
		str_arg = tokens->token_arg->arg_str;
	if (len_arg > 1 && is_digit)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	else
	{
		if (len_arg == 1 && is_digit && check_range(str_arg,
				&exit_code))
			exit(exit_code % 256);
		else
		{
			printf("exit: %s: numeric argument required\n", str_arg);
			exit(2);
		}
	}
	exit(exit_code);
}
