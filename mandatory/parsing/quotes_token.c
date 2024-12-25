/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:21 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/24 17:30:34 by rrakotos         ###   ########.fr       */
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

char	*handle_doubquotes(char **qts, char **result, t_tokens *token, int *is_expand)
{
	char	*trim;

	trim = remove_doubquotes(qts, *is_expand);
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
		else if (*mode_add == 2)
			last_arg(token->token_arg)->operand = VOIDTOKEN;
		else
			token->errnum = AMBIGUOUS;
	}
	if (!expand)
		expand = ft_calloc(1, sizeof(char));
	*result = concat_str(*result, expand);
	if (*mode_add != 4)
		*mode_add = 3;
}

int	is_valid_char(char c)
{
	return (c != '"' && c != '\'' && c != '\0' 
	&& c != '$' && c != ' ' && c != '>' && c != '<');
}

char	*parse_input(t_tokens *token, char **input, int *mode_add)
{
	char	*result;
	int		is_expand;

	if (!token)
		return (NULL);
	result = ft_calloc(1, sizeof(char));
	is_expand = 1;
	while (**input != ' ' && **input != '\0' && **input != '|' && token->errnum == DEFAULT)
	{
		// gérer double quotes
		if (**input == '"' && !handle_doubquotes(input, &result, token, &is_expand))
			return (NULL);
		// gérer un seule quotes
		if (**input == '\'' && !handle_onequotes(input, &result, token))
			return (NULL);
		// caractere normal de atao join tsikelikely
		if (is_valid_char(**input))
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		// si dollar mila jerena oe expandable ve : expandable raha tsy misy HEREDOC eo aloha sinon expand
		if (**input == '$')
		{
			if (is_expand)
				handle_var(input, &result, token, mode_add);
			else
			{
				result = concat_str(result, ft_substr(*input, 0, 1));
				(*input)++;
			}
		}
		// raha nisy cmd na arg avant operateur na vide "\0" anaty flow de stocke-na aloha
		if ((ft_strlen(result) > 0 || *mode_add == 4) && (**input == '>' || **input == '<'))
			return (result);
		// raha misy operateur de ajouter le operateur en créant un flow
		if ((**input == '>' || **input == '<') && !handle_flow(token, input, mode_add, &is_expand))
			return (free(result), NULL);
	}
	// averina ts vide ny cmd na arguments
	if (*mode_add == 1 && token->token_cmd->operand == VOIDTOKEN && ft_strlen(result) > 0)
		token->token_cmd->operand = NOTOP;
	else if (token->token_arg != NULL && *mode_add == 2 && last_arg(token->token_arg)->operand == VOIDTOKEN
		&& ft_strlen(result) > 0)
		last_arg(token->token_arg)->operand = NOTOP;
	return (result);
}
