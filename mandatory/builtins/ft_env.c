/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:15:44 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 10:25:03 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	if (*str != '-')
		return (1);
	str += (*str == '-');
	if (*str == '\0')
		return (2);
	else if (*str == '-' && *(str + 1) == '\0')
		return (3);
	return (4);
}

static void	show_env(void)
{
	t_data_env	*env;

	env = get_data_env();
	while (env != NULL)
	{
		if (env->key != NULL && env->value != NULL)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
}

static int	handle_error(int num_option, char *str)
{
	int	status_value;

	status_value = 0;
	if (num_option == 2)
		return (0);
	else if (num_option == 4)
	{
		ft_putstr_fd("env: invalid option -- ", 2);
		ft_putendl_fd(str, 2);
		status_value = 125;
	}
	else if (num_option == 3)
	{
		show_env();
		status_value = 0;
	}
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		status_value = 127;
	}
	return (status_value);
}

int	ft_env(t_tokens *token)
{
	t_arg	*args;
	int		status_option;

	args = token->token_arg;
	if (args && args->arg_str)
	{
		status_option = check_option(args->arg_str);
		return (handle_error(status_option, args->arg_str));
	}
	show_env();
	return (0);
}
