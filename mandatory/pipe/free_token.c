/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:14:50 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 09:46:00 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_arg		*tmp_arg;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->token_cmd->cmd_str);
		free(tmp->token_cmd);
		while (tmp->token_arg)
		{
			tmp_arg = tmp->token_arg;
			tmp->token_arg = tmp->token_arg->next_arg;
			free(tmp_arg->arg_str);
			free(tmp_arg);
		}
		free(tmp);
	}
	free(tokens);
}
