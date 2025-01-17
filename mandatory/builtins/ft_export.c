/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 15:17:51 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argv_export(char *arg_str)
{
	if (!ft_isalpha(*arg_str) && *arg_str != '_' && *arg_str != '-')
		return (-1);
	else if (*arg_str == '-' && *(arg_str + 1) != '\0')
		return (-2);
	while (*arg_str != '+' && *arg_str != '=' && *arg_str != '\0')
	{
		if (!ft_isalpha(*arg_str) && !ft_isdigit(*arg_str) && *arg_str != '_')
			return (-1);
		arg_str++;
	}
	if (*arg_str == '+' && *(arg_str + 1) == '=')
		return (1);
	else if (*arg_str == '+' && *(arg_str + 1) != '=')
		return (-1);
	return (0);
}

static void	export_to_env(char *value, int type_argv)
{
	t_data_env	*node;
	t_data_env	*var;
	t_data_env	*env;

	node = map_env(value);
	var = ft_getenv(node->key);
	if (!var)
	{
		env = get_data_env();
		addback_env(&env, node);
	}
	else if (var && node->value != NULL)
	{
		if (type_argv == 1 && var->value != NULL)
			var->value = concat_str(var->value, node->value);
		else
		{
			free(var->value);
			var->value = node->value;
		}
		free_node_tmp(node);
	}
	else if (var && node->value == NULL)
		free_node_tmp(node);
	load_data_export();
}

void	print_error_export(char *str, int type_check)
{
	if (type_check == -1)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	ft_putstr_fd("export: ", 2);
	ft_putchar_fd(*str, 2);
	ft_putchar_fd(*(str + 1), 2);
	ft_putendl_fd(": invalid option", 2);
}

static int	handle_arg_export(char *value, int type_arg, int *flag)
{
	int	n_exit;

	n_exit = 0;
	if (type_arg == -1 || (type_arg == -2 && *flag == 1))
	{
		*flag = 1;
		n_exit = 1;
		print_error_export(value, -1);
	}
	else if (type_arg == -2 && !*flag)
	{
		print_error_export(value, -2);
		*flag = 0;
		return (2);
	}
	if (type_arg >= 0)
		export_to_env(value, type_arg);
	return (n_exit);
}

int	ft_export(t_tokens *tokens)
{
	int			len_arg;
	int			type_arg;
	int			status;
	t_arg		*argv;
	static int	flag = 0;

	status = 0;
	argv = tokens->token_arg;
	len_arg = count_arg(argv);
	if (len_arg < 1 || !argv->arg_str)
	{
		display_env_export();
		return (status);
	}
	while (argv != NULL)
	{
		type_arg = check_argv_export(argv->arg_str);
		status = handle_arg_export(argv->arg_str, type_arg, &flag);
		if (status == 2)
			return (status);
		argv = argv->next_arg;
	}
	flag = 0;
	return (status);
}
