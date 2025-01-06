/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_fd_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:49:35 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/06 22:50:59 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  *static_fd_heredoc(void)
{
    static int  cst = -1;
    return (&cst);
}

int get_last_fd_heredoc(void)
{
    return (*static_fd_heredoc());
}

void    set_fd_heredoc(int fd)
{
    *static_fd_heredoc() = fd;
}