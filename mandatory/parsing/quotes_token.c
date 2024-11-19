/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:46:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/19 16:39:32 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*function(char *start, int *len_str, char **start_dollar)
{
	char	*str;
	char	*value_env;

	str = ft_substr(start, 0, *len_str);
	value_env = handle_dollar(start_dollar);
	str = ft_strjoin(str, value_env);
	*len_str = 0;
	free(value_env);
	return (str);
}

char	*remove_doubquotes(char **start_quotes)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	if (**start_quotes == '"')
		start = *start_quotes + 1;
	result = ft_calloc(1, sizeof(char));
	while (is_close < 2)
	{
		if (**start_quotes == '$')
		{
			result = ft_strjoin(result, function(start, &len, start_quotes));
			start = *start_quotes;
		}
		if (**start_quotes == '"')
			is_close++;
		if (**start_quotes != '"' && **start_quotes != '$')
			len++;
		if (is_close == 1 && **start_quotes == '\0')
			return (NULL);
		(*start_quotes)++;
	}
	if (len == 0 && ft_strlen(result) == 0)
		return (ft_strdup(""));
	if (len > 0)
		result = ft_strjoin(result, ft_substr(start, 0, len));
	return (result);
}

char	*remove_onequotes(char **start_quotes)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	start = *start_quotes;
	while (is_close < 2)
	{
		if (**start_quotes == '\'')
			is_close++;
		if (**start_quotes != '\'')
			len++;
		if (is_close == 1 && **start_quotes == '\0')
			return (NULL);
		(*start_quotes)++;
	}
	if (len == 0)
		return (ft_strdup(""));
	result = ft_substr(start, 1, len);
	return (result);
}

char	*trim_quotes(char **start_quotes)
{
	char	*result;
	char	*trim;

	result = ft_calloc(1, sizeof(char));
	while (**start_quotes != ' ' && **start_quotes != '\0'
		&& **start_quotes != '|')
	{
		if (**start_quotes == '"')
		{
			trim = remove_doubquotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			// printf("in doubquotes: %s\n", result);
			free(trim);
		}
		if (**start_quotes == '\'')
		{
			trim = remove_onequotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			// printf("in onequotes: %s\n", result);
			free(trim);
		}
		if (**start_quotes != '"' && **start_quotes != '\''
			&& **start_quotes != '\0' && **start_quotes != ' '
			&& **start_quotes != '$')
		{
			trim = ft_substr(*start_quotes, 0, 1);
			result = ft_strjoin(result, trim);
			free(trim);
			// printf("without: %s\n", result);
			(*start_quotes)++;
		}
		if (**start_quotes == '$')
		{
			if (*(*start_quotes + 1) == '"' || *(*start_quotes + 1) == '\'')
				(*start_quotes)++;
			else
				result = ft_strjoin(result, handle_dollar(start_quotes));
		}
	}
	return (result);
}
