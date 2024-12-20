/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/29 10:47:39 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(void)
{
	char	**env;

	env = get_data_export();
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

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
	t_data_env	**tmp;

	node = hash_env(value);
	var = ft_getenv(node->key);
	if (!var)
	{
		env = get_data_env();
		addback_env(&env, node);
	}
	else if (var && node->value != NULL)
	{
		tmp = &var;
		if (type_argv == 1 && (*tmp)->value != NULL)
			(*tmp)->value = ft_strjoin((*tmp)->value, node->value);
		else
			(*tmp)->value = node->value;
		free(node);
	}
	load_data_export();
}

static int	handle_arg_export(char *value, int type_arg)
{
	int	flag;
	int	nexit;

	flag = 0;
	nexit = 0;
	if (type_arg == -1)
	{
		flag = 1;
		nexit = 1;
		printf("export: `%s': not a valid identifier\n", value);
	}
	else if (type_arg == -2 && !flag)
	{
		printf("export: %c%c: invalid option\n", *(value), *(value + 1));
		return (2);
	}
	else
	{
		flag = 1;
		export_to_env(value, type_arg);
	}
	return (nexit);
}

int	ft_export(t_tokens *tokens)
{
	int		len_arg;
	int		type_arg;
	int		status;
	t_arg	*argv;

	status = 0;
	argv = tokens->token_arg;
	len_arg = count_arg(argv);
	if (len_arg < 1)
	{
		display_env();
		return (status);
	}
	while (argv != NULL)
	{
		type_arg = check_argv_export(argv->arg_str);
		status = handle_arg_export(argv->arg_str, type_arg);
		if (status == 2)
			return (status);
		argv = argv->next_arg;
	}
	return (status);
}
