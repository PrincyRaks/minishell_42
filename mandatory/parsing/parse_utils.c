/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/29 08:52:55 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	**store_token(char *input)
{
	int			is_cmd;
	t_tokens	*node_token;
	t_tokens	**first_node;
	t_cmd		*node_cmd;
	char *new_input;

	is_cmd = 0;
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

	}
	return (first_node);
}
