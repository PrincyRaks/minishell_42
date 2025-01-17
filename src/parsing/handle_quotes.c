/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:19:02 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 16:38:48 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar(char **start, int *len_str, char **start_dollar)
{
	char	*str;
	char	*value_env;

	str = ft_substr(*start, 0, *len_str);
	*len_str = 0;
	while (**start_dollar == '$')
	{
		value_env = handle_dollar(start_dollar);
		if (value_env)
			str = concat_str(str, value_env);
	}
	*start = *start_dollar;
	return (str);
}

char	*remove_doubquotes(char **qts, int is_expand)
{
	int		len;
	int		is_close;
	char	*result;
	char	*start;

	len = 0;
	is_close = 0;
	start = *qts + (**qts == '"');
	result = ft_calloc(1, sizeof(char));
	while (is_close < 2)
	{
		if (**qts == '$' && is_expand)
			result = concat_str(result, expand_dollar(&start, &len, qts));
		if (**qts == '"')
			is_close++;
		if (**qts != '"')
			len++;
		if (is_close == 1 && **qts == '\0')
			return (free(result), NULL);
		(*qts)++;
	}
	if (len > 0)
		result = concat_str(result, ft_substr(start, 0, len));
	return (result);
}

char	*remove_onequotes(char **qts)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	start = *qts;
	while (is_close < 2)
	{
		if (**qts == '\'')
			is_close++;
		if (**qts != '\'')
			len++;
		if (is_close == 1 && **qts == '\0')
			return (NULL);
		(*qts)++;
	}
	result = ft_substr(start, 1, len);
	return (result);
}
