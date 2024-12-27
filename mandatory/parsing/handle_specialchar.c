/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specialchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:58:28 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/26 23:05:59 by rrakotos         ###   ########.fr       */
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

char	*handle_doubquotes(char **qts, char **result, t_tokens *token, int is_expand)
{
	char	*trim;

	trim = remove_doubquotes(qts, is_expand);
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

static void	set_option3(int	*mode, t_tokens *token)
{
	t_arg	*end_arg;

	end_arg = last_arg(token->token_arg);
	if (*mode != 4 && *mode != 3 && (token->token_cmd->operand != VOIDTOKEN 
		|| (end_arg != NULL && end_arg->operand != VOIDTOKEN)))
		*mode = 3;
}

void	handle_var(char **input, char **res, t_tokens *token, int *mode)
{
	char	*expand;
	t_arg	*end_arg;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		(*input)++;
		return ;
	}
	expand = handle_dollar(input);
	if (!ft_strlen(*res) && !expand && (**input == ' ' || **input == '\0'
			|| **input == '|'))
	{
		end_arg = last_arg(token->token_arg);
		if (*mode == 1)
			token->token_cmd->operand = VOIDTOKEN;
		else if (*mode == 2 && end_arg != NULL)
			end_arg->operand = VOIDTOKEN;
		else if (*mode == 4)
			token->errnum = AMBIGUOUS;
	}
	if (!expand)
		expand = ft_calloc(1, sizeof(char));
	*res = concat_str(*res, expand);
	set_option3(mode, token);
}
