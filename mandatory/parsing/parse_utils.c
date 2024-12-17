/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/17 15:35:26 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;

	parsing = NULL;
	if (node_token->token_cmd != NULL && mode_add == 2 && node_token->token_cmd->operand == NOTOP)
	{
		if (!node_token->token_arg)
			node_token->token_arg = new_arg();
		else if (last_arg(node_token->token_arg)->operand != VOIDTOKEN)
			last_arg(node_token->token_arg)->next_arg = new_arg();
		parsing = parse_input(node_token, input, mode_add);
		if (!parsing)
			return (0);
		last_arg(node_token->token_arg)->arg_str = parsing;
		// mila gerena ny clean
		return (1);
	}
	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	if (node_token->token_cmd->operand == VOIDTOKEN)
		mode_add = 1;
	parsing = parse_input(node_token, input, mode_add);
	if (!parsing)
		return (0);
	node_token->token_cmd->cmd_str = parsing;
	mode_add = 2;
	// if (node_token->token_cmd->operand == VOIDTOKEN)
	// 	mode_add = 1;
	return (1);
}

static int	create_new_token(t_tokens **first_node, t_tokens **node_token)
{
	if (!node_token && !*node_token)
		return (0);
	*node_token = new_token();
	if (!node_token)
	{
		// mila gerer-na ny clean
		clean_tokens(first_node);
		return (0);
	}
	addback_token(first_node, *node_token);
	return (1);
}

static void	parse_void_instruction(t_tokens *token)
{
	t_arg	*arg_cmd;
	
	if (!token)
		return ;
	while (token != NULL)
	{
		if (token->token_cmd != NULL
			&& token->token_cmd->operand == VOIDTOKEN)
		{
			free(token->token_cmd->cmd_str);
			token->token_cmd->cmd_str = NULL;
		}
		arg_cmd = token->token_arg;
		while (arg_cmd != NULL)
		{
			if (arg_cmd->operand == VOIDTOKEN)
			{
				free(arg_cmd->arg_str);
				arg_cmd->arg_str = NULL;
			}
			arg_cmd = arg_cmd->next_arg;
		}
		token = token->next;
	}
}

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
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input != ' ' && *input != '\0' && *input != '|')
		{
			if (!store_token(node_token, &input))
			{
				printf("Tsy midy ny quotes\n");
				// break ;
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
					return (clean_tokens(first_node), NULL);
				input = new_input;
			}
			if (!create_new_token(first_node, &node_token))
				break ;
		}
		/* else if (*input == '>' || *input == '<')
		{
			input = parse_redirections(input, &node_token->token_arg);
			if (!input)
				return (clean_tokens(first_node), NULL);
		} */
	}
	parse_void_instruction(*first_node);
	printf("cmd: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("Misy vide ve?: %d\n", is_void_instruction(*first_node));
	// printf("arg1: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	// printf("number of node: %d\n", count_token(*first_node));
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	return (first_node);
}
