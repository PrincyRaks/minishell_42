/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:09:25 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 16:22:11 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_inquotes(t_tokens *token)
{
	t_arg	*end_arg;

	if (!token->token_cmd)
		token->token_cmd = new_cmd();
	if (token->token_cmd && !token->token_cmd->cmd_str)
	{
		token->token_cmd->operand = INQUOTES;
		return ;
	}
	end_arg = last_arg(token->token_arg);
	if (!end_arg)
	{
		token->token_arg = new_arg();
		end_arg = token->token_arg;
	}
	if (end_arg && !end_arg->arg_str)
		end_arg->operand = INQUOTES;
	if (end_arg && end_arg->operand == INQUOTES && end_arg->arg_str)
	{
		end_arg->next_arg = new_arg();
		end_arg->next_arg->operand = INQUOTES;
	}
}

void	set_option3(int *mode, t_tokens *token, char *expand)
{
	t_cmd	*cmd;
	t_arg	*end_arg;

	cmd = token->token_cmd;
	end_arg = last_arg(token->token_arg);
	if (*mode != 4 && *mode != 3 && ((cmd->operand == VOIDTOKEN
				&& ft_strlen(expand) > 0) || (end_arg != NULL
				&& end_arg->operand == VOIDTOKEN && expand
				&& ft_strlen(expand) > 0)))
		*mode = 3;
	else if (*mode != 4 && *mode != 3 && (cmd->operand != VOIDTOKEN
			|| (end_arg != NULL && end_arg->operand != VOIDTOKEN)))
		*mode = 3;
}

// create new arg if not exist & parse operand to type VOIDTOKEN
void	set_void_operand(t_tokens *token, int mode)
{
	t_arg	*end_arg;

	if (!token->token_cmd)
		token->token_cmd = new_cmd();
	if (mode == 1 && token->token_cmd->operand != INQUOTES)
	{
		token->token_cmd->operand = VOIDTOKEN;
		return ;
	}
	end_arg = last_arg(token->token_arg);
	if (!end_arg)
	{
		token->token_arg = new_arg();
		end_arg = token->token_arg;
	}
	if (mode == 2 && end_arg && !end_arg->arg_str
		&& end_arg->operand != INQUOTES)
		end_arg->operand = VOIDTOKEN;
	else if (mode == 2 && end_arg && end_arg->arg_str)
	{
		end_arg->next_arg = new_arg();
		end_arg->next_arg->operand = VOIDTOKEN;
	}
	if (mode == 4)
		token->errnum = AMBIGUOUS;
}

void	set_expandable_var_heredoc(t_tokens *node, t_flow *end_flow)
{
	t_cmd	*cmd;
	t_arg	*end_arg;

	if (!node)
		return ;
	cmd = node->token_cmd;
	end_arg = last_arg(node->token_arg);
	if (!end_flow)
		return ;
	if (cmd != NULL && !cmd->cmd_str && cmd->operand == INQUOTES
		&& !end_flow->word)
	{
		end_flow->expandable = 0;
		cmd->operand = NOTOP;
	}
	if (end_arg != NULL && !end_arg->arg_str && end_arg->operand == INQUOTES
		&& !end_flow->word)
	{
		end_flow->expandable = 0;
		end_arg->operand = NOTOP;
	}
}

// set void str(i.e: "") cmd or args verify with inquotes
void	set_void_str(t_tokens *token, char *void_str, int *mode)
{
	t_cmd	*cmd;
	t_arg	*end_arg;

	cmd = token->token_cmd;
	if (cmd && !cmd->cmd_str && cmd->operand == INQUOTES)
	{
		cmd->cmd_str = void_str;
		*mode = 2;
		return ;
	}
	end_arg = last_arg(token->token_arg);
	if (end_arg && !end_arg->arg_str && end_arg->operand == INQUOTES)
		end_arg->arg_str = void_str;
	*mode = 2;
}
