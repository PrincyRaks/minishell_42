/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:30:05 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/26 21:15:40 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	***static_data_export(void)
{
	static char	**cst = NULL;

	return (&cst);
}

char	**get_data_export(void)
{
	return (*static_data_export());
}

void	set_data_export(char **value)
{
	*static_data_export() = value;
}
