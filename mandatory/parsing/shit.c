
#include "minishell.h"

int	store_in_flow(t_tokens *node_token, char *parsing, int *mode_add)
{
	if (!node_token && !parsing)
		return ;
	// if (*mode_add == 4 && node_token->token_flow != NULL)
	// {
		last_flow(node_token->token_flow)->word = parsing;
		if (node_token->token_cmd != NULL && (node_token->token_cmd->cmd_str != NULL 
			|| node_token->token_cmd->operand == VOIDTOKEN))
			*mode_add = 1;
		if (node_token->token_cmd != NULL && mode_add == 2 && node_token->token_cmd->operand == NOTOP)
			*mode_add = 2;
		return (node_token->errnum)
	// }
}

static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;

	parsing = NULL;
	// arguments (2)
	if (node_token->token_cmd != NULL && mode_add == 2 && node_token->token_cmd->operand == NOTOP)
	{
		if (!node_token->token_arg)
			node_token->token_arg = new_arg();
		else if (last_arg(node_token->token_arg)->operand != VOIDTOKEN)
			last_arg(node_token->token_arg)->next_arg = new_arg();
		parsing = parse_input(node_token, input, &mode_add);
		if (!parsing)
			return (node_token->errnum);
		last_arg(node_token->token_arg)->arg_str = parsing;
		return (node_token->errnum);
	}
	// commandes (1)
	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	if (node_token->token_cmd->operand == VOIDTOKEN)
		mode_add = 1;
	parsing = parse_input(node_token, input, &mode_add);
	if (!parsing)
		return (node_token->errnum);
	if (mode_add != 4)
	{
		node_token->token_cmd->cmd_str = parsing;
		mode_add = 2;
	}
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL)
	{
		if (!parse_input)
		{
			parsing = parse_input(node_token, input, &mode_add);
			if (!parsing)
				return (node_token->errnum);
		}
		last_flow(node_token->token_flow)->word = parsing;
		if (node_token->token_cmd != NULL && (node_token->token_cmd->cmd_str != NULL 
			|| node_token->token_cmd->operand == VOIDTOKEN))
			mode_add = 1;
		if (node_token->token_cmd != NULL && mode_add == 2 && node_token->token_cmd->operand == NOTOP)
			mode_add = 2;
		return (node_token->errnum);
	}
	// if (node_token->token_cmd->operand == VOIDTOKEN)
	// 	mode_add = 1;
	return (node_token->errnum);
}
