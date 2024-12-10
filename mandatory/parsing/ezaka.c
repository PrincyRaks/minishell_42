/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezaka.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:23:36 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/10 14:54:28 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_parse_token(t_tokens *token, char *parse_input, int mode_add)
{
	// mode_add = 0->new cmd
	// mode_add = 1-> set value cmd
// miova 2 ny mode rah tapitra tanteraka le boucle ao;
	// mode_add = 2-> set value arg
	// mode_add = 3-> new arg
	if (token->token_cmd != NULL && (mode_add == 2 || mode_add == 3))
	{
		if (mode_add == 2)
			token->token_arg->arg_str = parse_input;
		else
			addback_arg(&node_token->token_arg, parse_input);
		return ;
	}
	if (!mode_add)
	{
		token->token_cmd = new_cmd();
		mode_add = 1;
	}
	token->token_cmd->cmd_str = parse_input;
}

static char	*handle_onequotes(char **qts, char **result, t_tokens *token, int *mode_add)
{
	char	*trim;

	trim = remove_onequotes(qts);
	// if error unclosed quotes
	if (!trim)
	{
		free(trim);
		free(*result);
		if (*mode_add == 1)
			token->token_cmd->errnum = UNQUOTES;
		else
			last_arg(token->token_arg)->errnum = UNQUOTES;
		return (NULL);
	}
	*result = concat_str(*result, trim);
	return (*result);
}

static char	*handle_doubquotes(char **qts, char **result)
{
	char	*trim;

	trim = remove_doubquotes(qts);
	// if error unclosed quotes
	if (!trim)
	{
		free(trim);
		free(*result);
		return (NULL);
	}
	*result = concat_str(*result, trim);
	return (*result);
}

static char	*handle_var(char **input, char **result, t_tokens *token)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
		(*input)++;
	else
	{
		expand = handle_dollar(input);
		// !!!eto le mi-verifier oe $variable ve NULL !!!!
		// if (strlen(*result) == 0 && expand == NULL) de NULL le argument zay
		if (expand != NULL)
			*result = concat_str(*result, expand);
	}
	return (*result);
}

t_errnum	check_errnum(t_tokens *token)
{
	t_arg	*arg_cmd;

	if (token->token_cmd && token->token_cmd->errnum != DEFAULT)
		return (token->token_cmd->errnum);
	arg_cmd = token->token_arg;
	while (arg_cmd != NULL)
	{
		if (arg_cmd->errnum != DEFAULT)
			return (arg_cmd->errnum);
		arg_cmd = arg_cmd->next_arg;
	}
	return (DEFAULT);
}

char	*store_parse_token(t_tokens *token, char **input, int *mode_add)
{
	char	*result;

	if (!token)
		return (NULL);
	result = ft_calloc(1, sizeof(char));
	while (**input != ' ' && **input != '\0' && **input != '|')
	{
		if (**input == '"' && handle_doubquotes(input, &result, token, mode_add) == NULL 
			&& check_errnum(token) == UNQUOTES)
			return (NULL);
		if (**input == '\'' && handle_onequotes(input, &result, token, mode_add) == NULL 
			&& check_errnum(token) == UNQUOTES)
			return (NULL);
		if (**input != '"' && **input != '\'' && **input != '\0'
			&& **input != ' ' && **input != '$')
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		if (**input == '$' && handle_var(input, &result, token) == NULL)
			return (NULL);
	}
	return (result);
}
