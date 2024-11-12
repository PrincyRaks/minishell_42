/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:59:16 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/08 16:45:14 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*create_node(void)
{
	t_tokens	*instr;

	instr = malloc(sizeof(t_tokens));
	if (!instr)
		return (NULL);
	// cmd
	instr->token_cmd = NULL;
	// arguments
	instr->token_arg = NULL;
	return (instr);
}
