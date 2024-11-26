/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tabenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:42:35 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/16 16:18:24 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_data_env(t_data_env *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}

char	**get_tabenv(void)
{
	int			i;
	char		*var;
	char		**env;
	int			len_data;
	t_data_env	*data_env;

	data_env = get_data_env();
	len_data = count_data_env(data_env);
	env = malloc(sizeof(t_data_env *) * (len_data + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (data_env != NULL && i < len_data)
	{
		var = ft_strdup(data_env->key);
		var = ft_strjoin(var, "=");
		var = ft_strjoin(var, data_env->value);
		env[i] = var;
		data_env = data_env->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
