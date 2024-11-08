/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:46:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/08 17:01:42 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_doubquotes(char **start_quotes)
{
	int		is_close;
	char	*result;
	int		len;
	char	*start;

	len = 0;
	is_close = 0;
	start = *start_quotes;
	while (**start_quotes && is_close < 2)
	{
		if (**start_quotes == '"')
			is_close++;
		if (**start_quotes != '"')
			len++;
		(*start_quotes)++;
	}
	if (is_close < 2)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	result = ft_substr(start, 1, len);
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
	while (**start_quotes && is_close < 2)
	{
		if (**start_quotes == '\'')
			is_close++;
		if (**start_quotes != '\'')
			len++;
		(*start_quotes)++;
	}
	if (is_close < 2)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	result = ft_substr(start, 1, len);
	return (result);
}

char	*trim_quotes(char **start_quotes)
{
	char *result;
	char *trim;
    int is_close;

	result = ft_calloc(1, sizeof(char));
    is_close = 0;
	while (**start_quotes != ' ' && is_close != 0)
	{
		if (**start_quotes != '"' && **start_quotes != '\''
			&& **start_quotes != '\0')
		{
			trim = ft_substr(*start_quotes, 0, 1);
			result = ft_strjoin(result, trim);
			free(trim);
			(*start_quotes)++;
		}
		else if (**start_quotes == '"')
		{
			trim = remove_doubquotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
		}
		else if (**start_quotes == '\'')
		{
			trim = remove_onequotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
		}
	}
	return (result);
}