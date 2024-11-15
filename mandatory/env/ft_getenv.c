/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:13:43 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 15:52:49 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data_env	*ft_getenv(char *var)
{
	t_data_env	*env;

	if (!var)
		return (NULL);
	env = get_data_env();
	while (env != NULL)
	{
		if (ft_strcmp(var, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
