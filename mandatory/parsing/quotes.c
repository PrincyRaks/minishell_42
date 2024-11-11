/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:18:50 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/11 13:56:49 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat(char *s1, char *s2)
{
	char	*new_s;
	char	*tmp_s1;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (*s1 && *s2)
		len++;
	new_s = ft_calloc((len + 1), 1);
	if (!new_s)
		return (free(s1), NULL);
	tmp_s1 = s1;
	while (*tmp_s1)
		*(new_s++) = *(tmp_s1++);
	if (*s1 && *s2)
		*(new_s++) = 32;
	while (*s2)
		*(new_s++) = *(s2++);
	free(s1);
	return (new_s - len);
}

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

char	*trim_quotes(char *str)
{
	char	*start;
	char	*result;
	char	*trim;

	start = str;
	result = ft_calloc(1, sizeof(char));
	while (*str)
	{
		if (*str != '"' && *str != '\'' && *str != '\0')
		{
			trim = ft_substr(str, 0, 1);
			result = ft_strjoin(result, trim);
			free(trim);
			str++;
		}
		if (*str == '"')
		{
			trim = remove_doubquotes(&str);
			if (!trim)
			{
				free(trim);
				free(start);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
		}
		if (*str == '\'')
		{
			trim = remove_onequotes(&str);
			if (!trim)
			{
				free(trim);
				free(start);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
		}
	}
	free(start);
	printf("result %zu\n", ft_strlen(result));
	return (result);
}

char	*handle_quotes(char *input)
{
	int		i;
	char	**cmd;
	char	*instrc;
	char	*trim;

	cmd = ft_split(input, ' ');
	if (!cmd)
		return (input);
	i = -1;
	instrc = ft_calloc(1, sizeof(char));
	while (cmd[++i] != NULL)
	{
		trim = trim_quotes(cmd[i]);
		if (!trim)
		{
			free(instrc);
			return (NULL);
		}
		instrc = concat(instrc, trim);
	}
	free(cmd);
	return (instrc);
}
