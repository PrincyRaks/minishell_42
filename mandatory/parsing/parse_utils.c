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

// mode(1): cmd | mode(2): arg(s) | mode(3): cmd in $var | mode(4): redir
static int	store_token(t_tokens *node_token, char **input)
{
	static int	mode_add = 1;
	char		*parsing;

	if (!node_token->token_cmd)
	{
		node_token->token_cmd = new_cmd();
		mode_add = 1;
	}
	parsing = parse_input(node_token, input, &mode_add);
	if (!parsing)
		return (node_token->errnum);
	if (mode_add == 3)
		return (store_var_element(node_token, parsing, &mode_add));
	if (valid_arguments(node_token, mode_add, parsing))
		return (store_parse_argument(node_token, parsing));
	if (mode_add == 1 && parsing != NULL)
		return (store_parse_cmd(node_token, parsing, &mode_add));
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
		return (store_parse_redir(node_token, parsing, &mode_add));
	return (node_token->errnum);
}

int	parse_pipe(char **input, t_tokens **node, t_tokens **first)
{
	if (!(*node)->token_cmd && !(*node)->token_flow)
		return (ERRPIPE);
	(*input)++;
	while (ft_isspace(**input))
		(*input)++;
	if (**input == '|' || **input == '\0')
		return (ERRPIPE);
	if (!create_new_token(first, node))
		return (ERRMALLOC);
	return (DEFAULT);
}

int	handle_token(char **input, t_tokens *node, t_tokens **first)
{
	t_errnum	err_token;

	err_token = DEFAULT;
	if (valid_store(**input))
	{
		err_token = store_token(node, input);
		if (err_token != DEFAULT && err_token != AMBIGUOUS)
		{
			print_errnum(node->errnum);
			(*first)->errnum = node->errnum;
			return (0);
		}
	}
	return (1);
}

int	handle_inline_pipe(char **input, t_tokens **node, t_tokens **first)
{
	int	errnum;

	errnum = parse_pipe(input, node, first);
	if (errnum > DEFAULT)
	{
		print_errnum(errnum);
		(*first)->errnum = errnum;
		return (0);
	}
	return (1);
}

t_tokens	**store_instruction(char *input)
{
	t_tokens	*node;
	t_tokens	**first_node;

	first_node = malloc(sizeof(t_tokens *));
	set_first_token(first_node);
	if (!first_node)
		return (NULL);
	node = new_token();
	*first_node = node;
	if (!node)
		return (NULL);
	while (*input && (node->errnum == DEFAULT || node->errnum == AMBIGUOUS))
	{
		while (ft_isspace(*input))
			input++;
		if (!handle_token(&input, node, first_node))
			break ;
		if (*input == '|' && !handle_inline_pipe(&input, &node, first_node))
			break ;
	}
	if ((*first_node)->errnum == DEFAULT || (*first_node)->errnum == AMBIGUOUS)
		parse_heredoc(*first_node);
	return (first_node);
}
