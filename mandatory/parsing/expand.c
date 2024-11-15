/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 15:55:04 by rrakotos         ###   ########.fr       */
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
	if (*var != NULL && **var != ' ' && **var != '\0')
	{
		while (**var != ' ' && **var != '\0' **var != '"')
			(*var)++;
		result = ft_substr(start, 1, (*var - start) - 1);
		data = ft_getenv(result);
        free(result);
		if (!data)
			return (ft_strdup(""));
		return (data->value);
	}
	return (start);
}
