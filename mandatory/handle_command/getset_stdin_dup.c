/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_stdin_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:32:42 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/15 09:00:07 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*static_stdin_dup(void)
{
	static int	cst = -1;

	return (&cst);
}

int	get_stdin_dup(void)
{
	return (*static_stdin_dup());
}

void	set_stdin_dup(int fd)
{
	*static_stdin_dup() = fd;
}
