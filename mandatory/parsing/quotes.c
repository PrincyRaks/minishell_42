/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:18:50 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/01 18:05:16 by rrakotos         ###   ########.fr       */
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

char	*trim_doubquotes(char *str)
{
	int		is_close;
	char	*start;
	size_t	len;
    char    *result;

	is_close = 0;
	len = 0;
	start = str;
	while (*str && is_close < 2)
	{
		if (*str == '"')
		{
			// if (is_close == 0 && *(str + 1) != '"')
			//     start = str;
			is_close++;
		}
		if (*str != '"')
			len++;
		str++;
	}
	if (len == 0)
        return (ft_strdup(""));
    result = ft_strchr(ft_substr(start, 1, len));
    if(result != NULL)
        trim_doubquotes()
	printf("inqotes: %s\n", ft_substr(start, 1, len));
	return (NULL);
}

char	*handle_quotes(char *input)
{
	int		i;
	char	**cmd;
	char	*instrc;

	// if ((count_char(input, '\'') % 2) == 1 && (count_char(input, '"')
	// 		% 2) == 1)
	if ((count_char(input, '"') % 2) == 1)
		return (input);
	cmd = ft_split(input, ' ');
	if (!cmd)
		return (input);
	i = -1;
	instrc = ft_calloc(1, sizeof(char));
	while (cmd[++i] != NULL)
	{
		instrc = concat(instrc, trim_doubquotes(cmd[i]));
	}
	// printf("Valiny: %s\n", instrc);
	return (input);
}
