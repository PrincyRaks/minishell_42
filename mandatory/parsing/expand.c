/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/16 16:59:36 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char **var)
{
	char		*result;
	t_data_env	*data;
	char		*start;

	start = *var;
	if (**var != '$')
		return (start);
	(*var)++;
	// reto gerer av eo "$$"=> $$ sy "$0" => "" sy "$'test'" => $'test'
	if (**var == '$' || ft_isdigit(**var) || !ft_isalpha(**var))
	{
		while (**var == '$')
		{
			result = ft_strdup("$");
			result = ft_strjoin(result, "$");
			(*var)++;
		}
		// eto nym ambiny
	}
	if (*var != NULL && **var != ' ' && **var != '\0')
	{
		while (**var != ' ' && **var != '\0' && **var != '"' && **var != '\''
			&& **var != '$')
			(*var)++;
		result = ft_substr(start, 1, (*var - start) - 1);
		data = ft_getenv(result);
		free(result);
		if (!data)
			return (ft_strdup(""));
		if (**var == '$')
			return (ft_strjoin(ft_strdup(data->value), expand(var)));
		return (ft_strdup(data->value));
	}
	return (ft_strdup("$"));
}
