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

void	ft_env(void)
{
	t_data_env	*env;

	env = get_data_env();
	while (env != NULL)
	{
		if (env->key != NULL && env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
