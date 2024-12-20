/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:21 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/20 11:57:30 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_onequotes(char **qts, char **result, t_tokens *token)
{
	char	*trim;

	trim = remove_onequotes(qts);
	if (!trim)
	{
		free(trim);
		free(*result);
		token->errnum = UNQUOTES;
		return (NULL);
	}
	*result = concat_str(*result, trim);
	return (*result);
}

char	*handle_doubquotes(char **qts, char **result, t_tokens *token)
{
	char	*trim;

	trim = remove_doubquotes(qts);
	if (!trim)
	{
		free(trim);
		free(*result);
		token->errnum = UNQUOTES;
		return (NULL);
	}
	*result = concat_str(*result, trim);
	return (*result);
}

static void	handle_var(char **input, char **result, t_tokens *token,
		int *mode_add)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		(*input)++;
		return ;
	}
	expand = handle_dollar(input);
	if (!ft_strlen(*result) && !expand && (**input == ' ' || **input == '\0'
			|| **input == '|'))
	{
		if (*mode_add == 1)
			token->token_cmd->operand = VOIDTOKEN;
		else
			last_arg(token->token_arg)->operand = VOIDTOKEN;
	}
	if (!expand)
		expand = ft_calloc(1, sizeof(char));
	*result = concat_str(*result, expand);
	*mode_add = 3;
}

int	is_char(char c)
{
	return (c != '"' && c != '\'' && c != '\0' && c != ' ' && c != '$'
		&& c != '>' && c != '<');
}

char	*parse_input(t_tokens *token, char **input, int *mode_add)
{
	char	*result;

	if (!token)
		return (NULL);
	result = ft_calloc(1, sizeof(char));
	while (**input != ' ' && **input != '\0' && **input != '|')
	{
		if (**input == '"' && !handle_doubquotes(input, &result, token))
			return (NULL);
		if (**input == '\'' && !handle_onequotes(input, &result, token))
			return (NULL);
		if (is_char(**input))
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		if (**input == '$')
			handle_var(input, &result, token, mode_add);
		if ((**input == '>' || **input == '<') && !handle_flow(token, input, mode_add))
			return (NULL);
	}
	if (*mode_add == 1 && token->token_cmd->operand == VOIDTOKEN
		&& ft_strlen(result) > 0)
		token->token_cmd->operand = NOTOP;
	else if (token->token_arg != NULL && *mode_add == 2
		&& last_arg(token->token_arg)->operand == VOIDTOKEN
		&& ft_strlen(result) > 0)
		last_arg(token->token_arg)->operand = NOTOP;
	return (result);
}
