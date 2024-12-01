/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:46:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/28 11:43:26 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_onequotes(char **qts, char **result)
{
	char	*trim;

	trim = remove_onequotes(qts);
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

static char	*handle_doubquotes(char **qts, char	**result)
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

static char	*handle_var(char **input, char **result)
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

// ovaina tokens ny argument anty hihihi !
char	*parse_input(char **input)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	while (**input != ' ' && **input != '\0'
		&& **input != '|')
	{
		if (**input == '"' && handle_doubquotes(input, &result) == NULL)
			return (NULL);
		if (**input == '\'' && handle_onequotes(input, &result) == NULL)
			return (NULL);
		if (**input != '"' && **input != '\'' && **input != '\0' 
			&& **input != ' ' && **input != '$')
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		if (**input == '$' && handle_var(input, &result) == NULL)
			return (NULL);
	}
	return (result);
}
