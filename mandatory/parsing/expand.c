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

char	*expand(char *var)
{
	int			i;
	char		*result;
	t_data_env	*data;

	i = 0;
	if (*var != '$')
		return (var);
	i++;
	if (var != NULL && var[i] != ' ' && var[i] != '\0')
	{
		while (var[i] != ' ')
			i++;
		result = ft_substr(var, 1, i - 1);
        printf("Variable: %s\n", result);
		data = ft_getenv(result);
        free(result);
		if (!data)
			return (ft_strdup(""));
		return (data->value);
	}
	return (var);
}
