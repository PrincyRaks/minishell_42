/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:03 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/19 12:30:33 by rrakotos         ###   ########.fr       */
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


// faharoa ato
char	*expand(char **var)
{
	char		*result;
	int			size;
	t_data_env	*data;

	// if (**var != '$')
	// 	return (*var);
	// (*var)++;
	if (*var == NULL || **var == ' ' || **var == '\0' || **var == '"')
		return (ft_strdup("$"));
	result = ft_calloc(sizeof(char), 1);
	size = 0;
	// est une variable env
	if (ft_isalpha(**var) || **var == '_')
	{
		while (ft_isalpha(**var) || ft_isdigit(**var) || **var == '_')
		{
			size++;
			(*var)++;
		}
		data = ft_getenv(ft_substr((*var) - size, 0, size));
		if (data != NULL)
			result = ft_strjoin(result, data->value);
		return (result);
	}
	// while (**var == '$')
	// {
	// 	result = ft_strjoin(result, "$");
	// 	(*var)++;
	// }
	// if (**var == '\0' || **var == '"')
	// 	return (ft_strjoin(result, "$"));
	// size = 0;
	// if (!ft_isalpha(**var) && **var != '_' && **var != '?')
	// {
	result = ft_strjoin(result, "$");
	while (*var != NULL && **var != ' ' && **var != '$' && **var != '\0')
	{
		size++;
		(*var)++;
	}
	result = ft_strjoin(result, ft_substr((*var) - size, 0, size));
	// }
	// if (**var == '$')
	// 	return (ft_strjoin(result, expand(var)));
	return (result);
}