/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/29 10:21:45 by rrakotos         ###   ########.fr       */
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

static int	check_type_argv(char *arg_str)
{
	if (!ft_isalpha(*arg_str) && *arg_str != '_')
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

static int	handle_arg(t_arg *argv)
{
	int			flag;
	int			type_arg;
	t_data_env	*node;
	t_data_env	*env;
	t_data_env	*var;
	t_data_env	**tmp;

	flag = 0;
	if (!argv)
	{
		display_env();
		return (0);
	}
	while (argv != NULL)
	{
		type_arg = check_type_argv(argv->arg_str);
		if (type_arg == -1)
		{
			flag = 1;
			printf("export: `%s': not a valid identifier\n", argv->arg_str);
			// return (1);
		}
		else if (type_arg == -2 && !flag)
		{
			printf("export: %s: invalid option\n", argv->arg_str);
			break ;
			// return (2);
		}
		else if (type_arg >= 0)
		{
			flag = 1;
			node = hash_env(argv->arg_str);
			var = ft_getenv(node->key);
			if (!var)
			{
				env = get_data_env();
				addback_env(&env, node);
			}
			else if (var && node->value != NULL)
			{
				tmp = &var;
				if (type_arg == 1 && (*tmp)->value != NULL)
					(*tmp)->value = ft_strjoin((*tmp)->value, node->value);
				else
					(*tmp)->value = node->value;
				free(node);
			}
			load_data_export();
		}
		argv = argv->next_arg;
	}
	return (0);
}

int	ft_export(t_tokens *tokens)
{
	int	len_arg;

	len_arg = count_arg(tokens->token_arg);
	if (len_arg < 1)
	{
		display_env();
		return (0);
	}
	return (handle_arg(tokens->token_arg));
}
