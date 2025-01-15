/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_num_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:35:47 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/08 10:01:05 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_num_file(void)
{
	static int	cst = -1;

	return (&cst);
}

int	get_last_file(void)
{
	return (*static_num_file());
}

void	set_num_file(int num_file)
{
	*static_num_file() = num_file;
}
