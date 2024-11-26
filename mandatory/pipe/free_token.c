/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:14:50 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 14:54:47 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_arg *args)
{
	t_arg	*current;
	t_arg	*next;

	current = args;
	while (current)
	{
		next = current->next_arg;
		free(current);            
		current = next;
	}
}

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!tokens)
		return;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->token_cmd)
			free(current->token_cmd->cmd_str);
		free(current->token_cmd);
		free_args(current->token_arg);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

