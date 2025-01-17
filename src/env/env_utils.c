/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:45:58 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/14 14:45:46 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data_env	*last_data(t_data_env *data)
{
	while (data)
	{
		if (!data->next)
			return (data);
		data = data->next;
	}
	return (NULL);
}

void	addback_env(t_data_env **lst, t_data_env *node)
{
	t_data_env	*end;

	if (lst)
	{
		if (!*lst)
			*lst = node;
		else
		{
			end = last_data(*lst);
			if (end)
				end->next = node;
		}
	}
}

t_data_env	*map_env(char *data)
{
	int			i;
	int			j;
	t_data_env	*node;

	node = malloc(sizeof(t_data_env));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	i = 0;
	while (data[i] != '=' && data[i] != '\0')
		i++;
	j = i;
	if (data[i - 1] == '+' && data[i] == '=')
		j = i - 1;
	node->key = ft_substr(data, 0, j);
	if (data[i] == '\0')
		return (node);
	i += (data[i] == '=');
	j = 0;
	while (data[i + j] != '\0')
		j++;
	node->value = ft_substr(data, i, j);
	return (node);
}

void	dup_env(char **env)
{
	int			i;
	t_data_env	*fisrt_data;

	i = -1;
	fisrt_data = NULL;
	while (env[++i] != NULL)
		addback_env(&fisrt_data, map_env(env[i]));
	set_data_env(fisrt_data);
	load_data_export();
}

void	display_env_export(void)
{
	char	**env;

	env = get_data_export();
	while (*env != NULL)
	{
		ft_putendl_fd(*env, STDOUT_FILENO);
		env++;
	}
}
