/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:40:54 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/11 23:40:54 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_sigint(void)
{
	static int	cst = 1;

	return (&cst);
}

int	get_sigint(void)
{
	return (*static_sigint());
}

void	set_sigint(int signal)
{
	*static_sigint() = signal;
}
