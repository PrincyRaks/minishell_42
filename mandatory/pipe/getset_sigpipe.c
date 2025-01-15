/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_sigpipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:56:21 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 13:57:29 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_sigpipe(void)
{
	static int	cst = 1;

	return (&cst);
}

int	get_sigpipe(void)
{
	return (*static_sigpipe());
}

void	set_sigpipe(int num_file)
{
	*static_sigpipe() = num_file;
}
