/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redemption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:52 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/12 16:22:38 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*store_token(char *input)
{
	int			is_cmd;
	t_tokens	*node;
	t_tokens	*first_node;
	t_cmd		node_cmd;

	is_cmd = 0;
	node = create_node();
	first_node = node;
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
			node = create_node();
			if (!node)
				return (NULL);
			addback_token(&first_node, node);
			input++;
		}
	}
	printf("cmd: %s\n", node->token_cmd->cmd_str);
	// printf("number of node: %d\n", count_token(first_node));
	// printf("arg: %s\n", first_node->token_arg->arg_cmd);
	return (first_node);
}
