/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_sigint_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:00:54 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/08 11:13:08 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  *static_sigint_hd(void)
{
    static int  cst = 1;
    return (&cst);
}

int get_sigint_hd(void)
{
    return (*static_sigint_hd());
}

void    set_sigint_hd(int signal)
{
    *static_sigint_hd() = signal;
}
