/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/10 11:32:53 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ovaina tanteraka fa tsy mety ty !!
// static void	store_token(t_tokens *node_token, char **input)
// {
// 	t_cmd	*node_cmd;

// 	if (node_token->token_cmd != NULL)
// 	{
// 		addback_arg(&node_token->token_arg, parse_input(node_token, input));
// 		// mila gerena ny clean
// 		return ;
// 	}
// 	// node_cmd = new_cmd();
// 	// node_cmd->cmd_str = parse_input(node_token, input);
// 	// if (!node_cmd->cmd_str)
// 	// 	node_cmd->errnum = UNQUOTES;
// 	// node_token->token_cmd = node_cmd;
// }

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
			store_token(node_token, &input);
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
	// printf("cmd: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("arg: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	// printf("number of node: %d\n", count_token(*first_node));
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	return (first_node);
}
