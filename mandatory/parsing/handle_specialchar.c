/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specialchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:58:28 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 11:10:28 by rrakotos         ###   ########.fr       */
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
	set_inquotes(token);
	return (*result);
}

char	*handle_doubquotes(char **qts, char **result, t_tokens *token,
		int is_expand)
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
	set_inquotes(token);
	return (*result);
}

void	handle_var(char **input, char **res, t_tokens *token, int *mode)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		(*input)++;
		return ;
	}
	if (ft_isdigit(*(*input + 1)))
	{
		(*input) += 2;
		return ;
	}
	expand = handle_dollar(input);
	if (!expand && (**input == ' ' || **input == '\0' || **input == '|'))
		set_void_operand(token, *mode);
	if (expand != NULL)
		*res = concat_str(*res, expand);
	set_option3(mode, token, expand);
}
