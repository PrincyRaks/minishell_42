/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:15:44 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/13 23:01:19 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_tokens *token)
{
	t_data_env	*env;
	t_arg	*args;

	args = token->token_arg;
	if (args && args->arg_str)
	{
		ft_putstr_fd(args->arg_str, 2);
		ft_putendl_fd(" : No such file or directory", 2);
		return (2);
	}
	env = get_data_env();
	while (env != NULL)
	{
		if (env->key != NULL && env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
