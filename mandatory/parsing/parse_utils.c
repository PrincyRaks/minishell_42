/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/19 16:41:34 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	**store_token(char *input)
{
	int			is_cmd;
	t_tokens	*node;
	t_tokens	**first_node;
	t_cmd		node_cmd;

	is_cmd = 0;
	first_node = malloc(sizeof(t_tokens *));
	if (!first_node)
		return (NULL);
	node = new_token();
	*first_node = node;
	if (!node)
		return (NULL);
	while (*input)
	{
		if (*input == ' ')
		{
			while (*input == ' ' && *input != '\0')
				input++;
		}
		if (*input != ' ' && *input != '\0')
		{
			if (!is_cmd)
			{
				node_cmd.cmd_str = trim_quotes(&input);
				node->token_cmd = &node_cmd;
				is_cmd = 1;
			}
			else
				addback_arg(&node->token_arg, trim_quotes(&input));
		}
		if (*input == '|')
		{
			node = new_token();
			if (!node)
				return (NULL);
			addback_token(first_node, node);
			input++;
		}
	}
	printf("cmd: %s\n", node->token_cmd->cmd_str);
	printf("number of node: %d\n", count_token(*first_node));
	// printf("arg: %s\n", first_node->token_arg->arg_cmd);
	// printf("arg2: %s\n", first_node->token_arg->next_arg->arg_cmd);
	return (first_node);
}
