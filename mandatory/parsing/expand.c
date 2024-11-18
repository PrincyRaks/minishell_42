/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/18 18:01:31 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // apres le premier $
// static int	is_var(char c)
// {
// 	if (c != '#' && c != '*' && c != '@' && c != '!' && !ft_isdigit(c))
// 		return (1);
// 	return (0);
// }

// static int check_prevvar(char *var)
// {

// }

char	*expand(char **var)
{
	char		*result;
	int			size;
	t_data_env	*data;

	if (**var != '$')
		return (*var);
	(*var)++;
	if (*var == NULL || **var == ' ' || **var == '\0')
		return (ft_strdup("$"));
	result = ft_calloc(sizeof(char), 1);
	size = 0;
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
		size = 0;
	}
	while (**var == '$')
	{
		result = ft_strjoin(result, "$");
		(*var)++;
	}
	if (**var == '\0' || **var == '"')
		return (ft_strjoin(result, "$"));
	size = 0;
	if (!ft_isalpha(**var) && **var != '_' && **var != '?' && **var != '"'
		&& **var != '\0')
	{
		result = ft_strjoin(result, "$");
		while (*var != NULL && **var != ' ' && **var != '$' && **var != '\0')
		{
			size++;
			(*var)++;
		}
		result = ft_strjoin(result, ft_substr((*var) - size, 0, size));
	}
	if (**var == '$')
		return (ft_strjoin(result, expand(var)));
	return (result);
}

// char	*expand(char **var)
// {
// 	char		*result;
// 	t_data_env	*data;
// 	char		*start;

// 	start = *var;
// 	if (**var != '$')
// 		return (start);
// 	(*var)++;
// 	if (*var != NULL && **var != ' ' && **var != '\0')
// 	{
// 		while (**var != ' ' && **var != '\0' && **var != '"' && **var != '\''
// 			&& **var != '$')
// 			(*var)++;
// 		result = ft_substr(start, 1, (*var - start) - 1);
// 		data = ft_getenv(result);
// 		free(result);
// 		if (!data)
// 			return (ft_strdup(""));
// 		if (**var == '$')
// 			return (ft_strjoin(ft_strdup(data->value), expand(var)));
// 		return (ft_strdup(data->value));
// 	}
// 	return (ft_strdup("$"));
// }
