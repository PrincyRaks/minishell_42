/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:29:31 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/20 16:19:48 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_cmd_var(t_tokens *token, char *parsing)
{
	int		i;
	char	**data;
	int		len_data;
	t_arg	*arg_cmd;
	t_arg	**first_arg;
	
	if (!parsing || !token)
		return ;
	data = ft_split(parsing, ' ');
	if (!data)
		return ;
	len_data = count_tab(data);
	if (len_data <= 0)
	{
		free_array(data);
		return ;
	}
	i = 0;
	if (token->token_cmd != NULL && token->token_cmd->cmd_str == NULL)
		token->token_cmd->cmd_str = data[i++];
	first_arg = &token->token_arg;
	arg_cmd = token->token_arg;
	while (i < len_data)
	{
		if (arg_cmd != NULL && arg_cmd->arg_str == NULL)
		{
			arg_cmd->arg_str = data[i];
			addback_arg(first_arg, arg_cmd);
			arg_cmd = arg_cmd->next_arg;
			i++;
		}
		if (!arg_cmd)
			arg_cmd = new_arg();
	}
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
	{
		store_cmd_var(node_token, parsing);
		return (node_token->errnum);
	}
	// arguments (2)
	if (node_token->token_cmd != NULL && mode_add == 2 
		&& node_token->token_cmd->operand == NOTOP && parsing != NULL)
	{
		if (!node_token->token_arg)
			node_token->token_arg = new_arg();
		else if (last_arg(node_token->token_arg)->operand != VOIDTOKEN)
			last_arg(node_token->token_arg)->next_arg = new_arg();
		last_arg(node_token->token_arg)->arg_str = parsing;
		return (node_token->errnum);
	}
	if (node_token->token_cmd->operand == VOIDTOKEN && mode_add != 4)
		mode_add = 1;
	if (mode_add == 1 && parsing != NULL)
	{
		node_token->token_cmd->cmd_str = parsing;
		mode_add = 2;
	}
	// redirections (4)
	if (mode_add == 4 && node_token->token_flow != NULL && parsing != NULL)
	{
		last_redir = last_flow(node_token->token_flow);
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
	while (*input && node_token->errnum == DEFAULT)
	{
		while (*input == ' ')
			input++;
		if (*input != ' ' && *input != '\0' && *input != '|')
		{
			// stop minishell print error num and clean all allocations
			if (store_token(node_token, &input) != DEFAULT)
			{
				printf("Erreur minishell: %d\n", node_token->errnum);
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
	parse_void_instruction(*first_node);
	// printf("cmd: %s\n", (*first_node)->token_cmd->cmd_str);
	// printf("arg1: %s\n", (*first_node)->token_arg->arg_str);
	// printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	// printf("number of node: %d\n", count_token(*first_node));
	// // printf("arg2: %s\n", (*first_node)->token_arg->next_arg->arg_str);
	// printf("operand: %d | file: %s\n", (*first_node)->token_flow->operand, (*first_node)->token_flow->word);
	// printf("operand: %d | file: %s\n", (*first_node)->token_flow->next_flow->operand, (*first_node)->token_flow->next_flow->word);
	// printf("operand: %d | file: %s\n", (*first_node)->token_flow->next_flow->next_flow->operand, (*first_node)->token_flow->next_flow->next_flow->word);
	return (first_node);
}
