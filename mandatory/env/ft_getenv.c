/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:13:43 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/13 17:34:07 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// zvtra efa expandable no atao anaty ty fonction ty
t_data_env	*ft_getenv(char *var)
{
	t_data_env	*env;

	if (!var)
		return (NULL);
	// if (*var != '$')
	// 	return (NULL);
	env = get_data_env();
	while (env != NULL)
	{
		if (ft_strcmp(var, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
