/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tabenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:42:35 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/26 15:48:39 by rrakotos         ###   ########.fr       */
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
	env = malloc(sizeof(char *) * (len_data + 1));
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

char	**get_tabkeys(void)
{
	int			i;
	int			len_data;
	char		**tabkeys;
	t_data_env	*data_env;

	data_env = get_data_env();
	len_data = count_data_env(data_env);
	tabkeys = malloc(sizeof(char *) * (len_data + 1));
	if (!tabkeys)
		return (NULL);
	i = 0;
	while (data_env != NULL && i < len_data)
	{
		tabkeys[i] = ft_strdup(data_env->key);
		data_env = data_env->next;
		i++;
	}
	tabkeys[i] = NULL;
	return (tabkeys);
}

static void	add_prefix(char **keys)
{
	int		i;
	int		len_tab;
	char	*tmp;
	char	*value;

	i = -1;
	len_tab = count_tab(keys);
	while (++i < len_tab)
	{
		value = ft_getenv(keys[i])->value;
		tmp = ft_strjoin(keys[i], "=");
		tmp = ft_strjoin(tmp, "\"");
		tmp = ft_strjoin(tmp, value);
		tmp = ft_strjoin(tmp, "\"");
		keys[i] = ft_strjoin(ft_strdup("declare -x "), tmp);
		free(tmp);
	}
}

void	get_envrange(void)
{
	int		i;
	int		j;
	char	**keys;
	char	*tmp;

	i = 0;
	keys = get_tabkeys();
	while (keys[i] != NULL)
	{
		j = i + 1;
		while (keys[j] != NULL)
		{
			if (ft_strcmp(keys[i], keys[j]) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
	add_prefix(keys);
	set_data_export(keys);
}
