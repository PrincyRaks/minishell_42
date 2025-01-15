/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:17:26 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 16:42:56 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_status(void)
{
	static int	cst = 0;

	return (&cst);
}

int	get_status(void)
{
	return (*static_status());
}

void	set_status(int fd)
{
	*static_status() = fd;
}
