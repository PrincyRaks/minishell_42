/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:09:29 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 10:34:47 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data_env	**static_data_env(void)
{
	static t_data_env	*cst = NULL;

	return (&cst);
}

t_data_env	*get_data_env(void)
{
	return (*static_data_env());
}

void	set_data_env(t_data_env *value)
{
	*static_data_env() = value;
}
