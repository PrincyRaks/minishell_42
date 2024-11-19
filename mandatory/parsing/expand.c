/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/19 16:18:42 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_dollar(char *dollar)
{
	int	i;

	i = 0;
	while (dollar[i] == '$')
		i++;
	return (i);
}

static char	*dupnd_dollar(int nb_dollar)
{
	char	*str;

	str = ft_calloc(sizeof(char), 1);
	while (nb_dollar > 0)
	{
		str = ft_strjoin(str, "$");
		nb_dollar--;
	}
	return (str);
}

char	*handle_dollar(char **var)
{
	char	*result;
	int		nb_dollar;

	if (**var != '$')
		return (*var);
	nb_dollar = count_dollar(*var);
	if ((nb_dollar % 2) == 0)
	{
		result = dupnd_dollar(nb_dollar);
		*var = *var + nb_dollar;
		return (result);
	}
	result = dupnd_dollar(nb_dollar - 1);
	*var = *var + (nb_dollar);
	result = ft_strjoin(result, expand(var));
	return (result);
}

char	*expand(char **var)
{
	char		*result;
	int			size;
	t_data_env	*data;

	if (*var == NULL || **var == ' ' || **var == '\0' || **var == '"')
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
		return (result);
	}
	result = ft_strjoin(result, "$");
	while (*var != NULL && **var != ' ' && **var != '$' && **var != '\0'
		&& **var != '\'' && **var != '"')
	{
		size++;
		(*var)++;
	}
	result = ft_strjoin(result, ft_substr((*var) - size, 0, size));
	return (result);
}
