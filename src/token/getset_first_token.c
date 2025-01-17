/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_first_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:58:05 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 21:16:37 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	***static_first_token(void)
{
	static t_tokens	**cst = NULL;

	return (&cst);
}

t_tokens	**get_first_token(void)
{
	return (*static_first_token());
}

void	set_first_token(t_tokens **first)
{
	*static_first_token() = first;
}
