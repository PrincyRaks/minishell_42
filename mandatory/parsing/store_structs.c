/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:50:08 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/30 20:22:11 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_array_element(t_tokens *token, char **data, int len_data, int *mode)
{
	int		i;
	t_arg	*arg_cmd;
	t_arg	*arg_new;
	t_arg	**first_arg;

	i = 0;
	arg_new = NULL;
	arg_cmd = token->token_arg;
	first_arg = &token->token_arg;
	if (token->token_cmd != NULL && token->token_cmd->cmd_str == NULL)
		token->token_cmd->cmd_str = data[i++];
	if (!token->token_arg)
	{
		arg_cmd = new_arg();
		arg_cmd->arg_str = data[i++];
		addback_arg(first_arg, arg_cmd);
	}
	while (arg_cmd != NULL && arg_cmd->arg_str != NULL)
		arg_cmd = arg_cmd->next_arg;
	while (i < len_data)
	{
		if (!arg_cmd)
		{
			arg_new = new_arg();
			arg_new->arg_str = data[i++];
			addback_arg(first_arg, arg_new);
		}
		if (arg_cmd != NULL && arg_cmd->arg_str == NULL)
		{
			arg_cmd->arg_str = data[i++];
			// addback_arg(first_arg, arg_cmd);
			arg_cmd = arg_cmd->next_arg;
		}
	}
	*mode = 2;
	free(data);
}

int	store_var_element(t_tokens *token, char *parsing, int *mode)
{
	char	**data;
	int		len_data;
	
	if (!parsing || !token)
		return (token->errnum);
	data = ft_split(parsing, ' ');
	if (!data)
	{
		token->errnum = ERRMALLOC;
		return (token->errnum);
	}
	len_data = count_tab(data);
	if (len_data <= 0 && parsing && (*parsing == '\0' || is_onlyspace(parsing)))
	{
		free(parsing);
		free_array(data);
		set_void_str(token, parsing, mode);
		return (token->errnum);
	}
	set_array_element(token, data, len_data, mode);
	free(parsing);
	return (token->errnum);
}

int	store_parse_argument(t_tokens *node, char *str_parse)
{
	t_arg	*end_arg;

	end_arg = last_arg(node->token_arg);
	if (!end_arg)
	{
		node->token_arg = new_arg();
		end_arg = node->token_arg;
	}
	else if (end_arg && 
		((end_arg->operand == NOTOP && end_arg->arg_str != NULL) 
		|| (end_arg->operand == INQUOTES && end_arg->arg_str != NULL) 
		|| ft_strlen(end_arg->arg_str) > 0))
		end_arg->next_arg = new_arg();
	// averina NULL rah toa ka $notexit
	if (end_arg->operand == VOIDTOKEN && end_arg->arg_str 
		&& !ft_strlen(end_arg->arg_str) && !ft_strlen(str_parse))
	{
		free(end_arg->arg_str);
		free(str_parse);
		end_arg->arg_str = NULL;
		return (node->errnum);
	}
	end_arg = last_arg(end_arg);
	end_arg->arg_str = str_parse;
	return (node->errnum);
}

int	store_parse_cmd(t_tokens *node, char *str_parse, int *mode)
{
	t_cmd	*cmd;

	cmd = node->token_cmd;
	// averina NULL rah toa ka $notexit
	if (cmd && cmd->operand == VOIDTOKEN && !cmd->cmd_str 
		&& !ft_strlen(cmd->cmd_str) && !ft_strlen(str_parse))
	{
		free(cmd->cmd_str);
		free(str_parse);
		cmd->cmd_str = NULL;
		return (node->errnum);
	}
	cmd->cmd_str = str_parse;
	if (cmd->operand != VOIDTOKEN && *mode != 4)
		*mode = 2;
	return (node->errnum);
}

int	store_parse_redir(t_tokens *node, char *str_parse, int *mode)
{
	t_flow	*last_redir;

	last_redir = last_flow(node->token_flow);
	set_expandable_var_heredoc(node, last_redir);
	last_redir->word = str_parse;
	if (node->token_cmd != NULL && (node->token_cmd->cmd_str == NULL 
		|| node->token_cmd->operand == VOIDTOKEN))
		*mode = 1;
	else if (node->token_cmd != NULL && node->token_cmd->operand == NOTOP)
		*mode = 2;
	return (node->errnum);
}
