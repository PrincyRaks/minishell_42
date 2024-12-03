/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/03 11:39:33 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	store_token(t_tokens *node_token, char **input)
{
	t_cmd	*node_cmd;

	if (node_token->token_cmd != NULL)
	{
		addback_arg(&node_token->token_arg, parse_input(input));
		return ;
	}
	node_cmd = new_cmd();
	node_cmd->cmd_str = parse_input(input);
	if (!node_cmd->cmd_str)
		node_cmd->errnum = UNQUOTES;
	node_token->token_cmd = node_cmd;
}

static int	create_new_token(t_tokens **first_node)
{
	t_tokens	*node_token;

	node_token = new_token();
	if (!node_token)
		return (0);
	addback_token(first_node, node_token);
	return (1);
}

t_tokens	**store_instruction(char *input)
{
	t_tokens	*node_token;
	t_tokens	**first_node;
	char *new_input;

	first_node = malloc(sizeof(t_tokens *));
	if (!first_node)
		return (NULL);
	node_token = new_token();
	*first_node = node_token;
	if (!node_token)
		return (NULL);
	while (*input)
	{
		 if (*input != ' ' && *input != '\0' && *input != '|')
		{
			if (!is_cmd)
			{
				node_cmd = new_cmd();
				node_cmd->cmd_str = trim_quotes(&input);
				if (!node_cmd->cmd_str)
					node_cmd->errnum = UNQUOTES;
				node_token->token_cmd = node_cmd;
				is_cmd = 1;
			}
			else
				addback_arg(&node_token->token_arg, trim_quotes(&input));
		}
		else if (*input == '|')
		{
			input++;
			while (*input == ' ')
				input++;
			if (*input == '\0')
			{
				new_input = readline("> ");
				while (new_input && *new_input == '\0')
					new_input =  readline("> ");
				if (!new_input)
					return (clean_tokens(first_node), NULL);
				input = new_input;
			}	
			node_token = new_token();
			if (!node_token)
				return (clean_tokens(first_node), NULL);
			addback_token(first_node, node_token);
			is_cmd = 0;
		}
		/* else if (*input == '>' || *input == '<')
		{
			input = parse_redirections(input, &node_token->token_arg);
			if (!input)
				return (clean_tokens(first_node), NULL);
		} */
	}
	printf("cmd: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("number of node: %d\n", count_token(*first_node));
	// printf("arg: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	return (first_node);
}
