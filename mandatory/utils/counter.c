/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:16:03 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/13 12:46:02 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tab(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	count_char(char *str, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

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
