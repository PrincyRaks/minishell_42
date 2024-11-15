/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redemption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:52 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 16:20:02 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_me(char *start, int *len_str, char **start_dollar)
{
	char	*str;

	str = ft_substr(start, 1, len_str);
	str = ft_strjoin(str, expand(start_dollar));
	return (str);
}

char	*remove_doubquotes(char **start_quotes)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	start = *start_quotes;
	result = ft_calloc(1, sizeof(char));
	while (is_close < 2)
	{
		if (**start_quotes == '"')
			is_close++;
		if (**start_quotes != '"' && **start_quotes != '$')
			len++;
		if (**start_quotes == '$')
		{
			// substratc + expand + join
		}
		if (is_close == 1 && **start_quotes == '\0')
			return (NULL);
		(*start_quotes)++;
	}
	if (len == 0)
		return (ft_strdup(""));
	// result = ft_substr(start, 1, len);
	return (result);
}

t_tokens	**store_token(char *input)
{
	int			is_cmd;
	t_tokens	*node;
	t_tokens	**first_node;
	t_cmd		node_cmd;

	is_cmd = 0;
	first_node = malloc(sizeof(t_tokens*));
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
	// printf("number of node: %d\n", count_token(first_node));
	// printf("arg: %s\n", first_node->token_arg->arg_cmd);
	// printf("arg2: %s\n", first_node->token_arg->next_arg->arg_cmd);
	return (first_node);
}
