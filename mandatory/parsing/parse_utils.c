/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/30 18:16:54 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_expandable_var_heredoc(t_tokens *node, t_flow *end_flow)
{
	t_cmd	*cmd;
	t_arg	*end_arg;

	if (!node)
		return ;
	cmd = node->token_cmd;
	end_arg = last_arg(node->token_arg);
	if (!end_flow)
		return ;
	if(cmd != NULL && !cmd->cmd_str && cmd->operand == INQUOTES && !end_flow->word)
	{
		end_flow->expandable = 0;
		cmd->operand = NOTOP;
	}
	if (end_arg != NULL && !end_arg->arg_str && end_arg->operand == INQUOTES && !end_flow->word)
	{
		end_flow->expandable = 0;
		end_arg->operand = NOTOP;
	}
}

int	valid_arguments(t_tokens *node, int mode_add, char *str_parsing)
{
	return (node->token_cmd != NULL && mode_add == 2 && str_parsing != NULL);
}

static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;
	t_flow		*last_redir;

	// commandes (1)
	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	parsing = parse_input(node_token, input, &mode_add);
	if (!parsing)
		return (node_token->errnum);
	// commande in variable (3)
	if (mode_add == 3)
		return (store_var_element(node_token, parsing, &mode_add));
	// arguments (2)
	if (valid_arguments(node_token, mode_add, parsing))
		return (store_parse_argument(node_token, parsing));
	if (mode_add == 1 && parsing != NULL)
		return (store_parse_cmd(node_token, parsing, &mode_add));
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
	{
		last_redir = last_flow(node_token->token_flow);
		// veririfier si heredoc peut faire un parsing du $variable ou non
		set_expandable_var_heredoc(node_token, last_redir);
		last_redir->word = parsing;
		if (node_token->token_cmd != NULL && (node_token->token_cmd->cmd_str == NULL 
			|| node_token->token_cmd->operand == VOIDTOKEN))
			mode_add = 1;
		else if (node_token->token_cmd != NULL && node_token->token_cmd->operand == NOTOP)
			mode_add = 2;
		return (node_token->errnum);
	}
	return (node_token->errnum);
}

// static void	parse_void_instruction(t_tokens *token)
// {
// 	t_arg	*arg_cmd;

// 	while (token != NULL)
// 	{
// 		if (token->token_cmd && token->token_cmd->operand == VOIDTOKEN 
// 			&& token->token_cmd->cmd_str)
// 		{
// 			free(token->token_cmd->cmd_str);
// 			token->token_cmd->cmd_str = NULL;
// 			token->token_cmd->operand = NOTOP;
// 		}
// 		arg_cmd = token->token_arg;
// 		while (arg_cmd != NULL)
// 		{
// 			if (arg_cmd->operand == VOIDTOKEN)
// 			{
// 				free(arg_cmd->arg_str);
// 				arg_cmd->arg_str = NULL;
// 			at << 1 <	arg_cmd->operand = NOTOP;
// 			}
// 			arg_cmd = arg_cmd->next_arg;
// 		}
// 		token = token->next;
// 	}
// }

t_tokens	**store_instruction(char *input)
{
	t_tokens	*node_token;
	t_tokens	**first_node;
	char		*new_input;

	first_node = malloc(sizeof(t_tokens *));
	if (!first_node)
		return (NULL);
	node_token = new_token();
	*first_node = node_token;
	if (!node_token)
		return (NULL);
	while (*input && node_token->errnum == DEFAULT)
	{
		while (*input == ' ')
			input++;
		if (*input != ' ' && *input != '\0' && *input != '|')
		{
			if (store_token(node_token, &input) != DEFAULT)
			{
				print_errnum(node_token->errnum);
				break ;
			}
		}
		if (*input == '|')
		{
			input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
			{
				new_input = readline("> ");
				while (new_input && *new_input == '\0')
					new_input = readline("> ");
				if (!new_input)
				{
					clean_tokens(first_node);
					return (NULL);
				}
				input = new_input;
			}
			if (!create_new_token(first_node, &node_token))
				break ;
		}
	}
	parse_heredoc(*first_node);
	// parse_void_instruction(*first_node);
	// printf("cmd1: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("arg1: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	// printf("count arg: %d\n", count_arg((*first_node)->token_arg));
	// printf("number of node: %d\n", count_token(*first_node));
	// printf("cmd2: %s\n", (*first_node)->next->token_cmd->cmd_str);
	// printf("cmd2 arg2: %s\n", (*first_node)->next->token_arg->arg_str);
	// printf("operand: %d | file: %s | expandable: %d\n", (*first_node)->token_flow->operand, (*first_node)->token_flow->word, (*first_node)->token_flow->expandable);
	// printf("operand: %d | file: %s\n", (*first_node)->next->token_flow->operand, (*first_node)->next->token_flow->word);
	// printf("operand: %d | file: %s | expandable: %d\n", (*first_node)->token_flow->next_flow->operand, (*first_node)->token_flow->next_flow->word,(*first_node)->token_flow->next_flow->expandable);
	// printf("operand: %d | file: %s\n", (*first_node)->token_flow->next_flow->next_flow->operand, (*first_node)->token_flow->next_flow->next_flow->word);
	return (first_node);
}
