/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:17:26 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/07 22:18:37 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  *static_status(void)
{
    static int  cst = 0;
    return (&cst);
}

int get_status(void)
{
    return (*static_status());
}

void    set_status(int fd)
{
    *static_status() = fd;
}
