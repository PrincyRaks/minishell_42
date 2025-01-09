/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:48:42 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/16 22:08:17 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_data_env **lst)
{
	t_data_env	*tmp;

	while (*lst != NULL)
	{
		if ((*lst)->key != NULL)
			free((*lst)->key);
		if ((*lst)->value != NULL)
			free((*lst)->value);
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

void	clean_node_env(t_data_env *node)
{
	if (!node)
		return ;
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}

void	clear_export_env(void)
{
	char	**data_export;

	data_export = get_data_export();
	if (!data_export)
		return ;
	free_array(data_export);
}
