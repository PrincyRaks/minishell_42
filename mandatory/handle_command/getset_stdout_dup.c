/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_stdout_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:30:32 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/15 09:44:31 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_stdout_dup(void)
{
	static int	cst = -1;

	return (&cst);
}

int	get_stdout_dup(void)
{
	return (*static_stdout_dup());
}

void	set_stdout_dup(int fd)
{
	*static_stdout_dup() = fd;
}
