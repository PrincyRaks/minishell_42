/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:47 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/14 11:20:26 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *s)
{
	int	flag;

	flag = 0;
	while (*s)
	{
		if (!ft_isdigit(*s) && !ft_isspace(*s) && *s != '+' && *s != '-')
			return (0);
		while (ft_isspace(*s))
			s++;
		if ((*s == '+' || *s == '-') && !ft_isdigit(*(s + 1)))
			return (0);
		if ((*s == '+' || *s == '-') && ft_isdigit(*(s + 1)))
			s++;
		if (ft_isdigit(*s))
			flag++;
		while (ft_isdigit(*s))
		{
			if (flag > 1)
				return (0);
			s++;
		}
	}
	if (!flag)
		return (0);
	return (1);
}

static int	check_range(char *str, long long *n_exit)
{
	int	i;
	int	negative;

	negative = str[0] == '-';
	i = str[0] == '-' || str[0] == '+';
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (*n_exit > 922337203685477580)
			return (*n_exit = 0);
		else if (!negative && *n_exit == 922337203685477580 && (str[i] - '0')
			% 10 > 7)
			return (*n_exit = 0);
		else if (negative && *n_exit == 922337203685477580 && (str[i] - '0')
			% 10 > 8)
			return (*n_exit = 0);
		if (ft_isdigit(str[i]))
			*n_exit = *n_exit * 10 + (str[i] - '0');
		i++;
	}
	if (negative)
		*n_exit *= -1;
	return (1);
}

void	print_error_exit(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(t_tokens *tokens)
{
	int			len_arg;
	char		*str_arg;
	long long	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	len_arg = 0;
	exit_code = 0;
	if (tokens && tokens->token_arg)
		len_arg = count_arg(tokens->token_arg);
	if (len_arg == 0)
		clean_up_exit(0);
	str_arg = tokens->token_arg->arg_str;
	if (len_arg > 1)
	{
		if (is_numeric(str_arg) && check_range(str_arg, &exit_code))
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	if (is_numeric(str_arg) && check_range(str_arg, &exit_code))
		clean_up_exit(exit_code % 256);
	print_error_exit(str_arg);
	clean_up_exit(2);
	return (0);
}
