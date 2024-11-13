/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:45:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/13 17:04:56 by rrakotos         ###   ########.fr       */
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

t_data_env	*hash_env(char *data)
{
	int			i;
	int			j;
	t_data_env	*node;

	node = malloc(sizeof(t_data_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	i = -1;
	while (data[++i] != '=')
		;
	node->key = ft_substr(data, 0, i);
	if (data[i] == '=')
		i++;
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
		addback_env(&fisrt_data, hash_env(env[i]));
	set_data_env(fisrt_data);
}

void	clean_env(t_data_env **lst)
{
	t_data_env	*tmp;

	while ((*lst)->next != NULL)
	{
		free((*lst)->key);
		free((*lst)->value);
		tmp = (*lst)->next;
		free(*lst);
	}
}
