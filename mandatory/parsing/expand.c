/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:33 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 13:55:19 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dollar(char *dollar)
{
	int	i;

	i = 0;
	while (dollar[i] != '$' && dollar[i] != '\0')
		i++;
	while (dollar[i] == '$')
		i++;
	return (i);
}

char	*dupnb_dollar(int nb_dollar)
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

char	*get_valuekey(char **var)
{
	int			size;
	char		*key;
	t_data_env	*data;

	size = 0;
	while (ft_isalpha(**var) || ft_isdigit(**var) || **var == '_')
	{
		size++;
		(*var)++;
	}
	key = ft_substr((*var) - size, 0, size);
	data = ft_getenv(key);
	free(key);
	if ((!data || !data->value))
		return (NULL);
	return (ft_strdup(data->value));
}

char	*expand(char **var)
{
	int		size;
	char	*result;

	if (*var == NULL || ft_isspace(**var) || **var == '\0' || **var == '"')
		return (ft_strdup("$"));
	size = 0;
	result = ft_calloc(sizeof(char), 1);
	if (**var == '?')
	{
		(*var)++;
		free(result);
		return (ft_itoa(get_status()));
	}
	if (**var != '?' && (ft_isalpha(**var) || **var == '_'))
		return (free(result), get_valuekey(var));
	result = ft_strjoin(result, "$");
	while (*var != NULL && !ft_isspace(**var) && **var != '$' && **var != '\0'
		&& **var != '\'' && **var != '"')
	{
		size++;
		(*var)++;
	}
	result = concat_str(result, ft_substr((*var) - size, 0, size));
	return (result);
}

char	*handle_dollar(char **var)
{
	char	*result;
	int		nb_dollar;
	char	*extend;

	if (**var != '$')
		return (*var);
	nb_dollar = count_dollar(*var);
	if ((nb_dollar % 2) == 0)
	{
		result = dupnb_dollar(nb_dollar);
		*var = *var + nb_dollar;
		return (result);
	}
	result = dupnb_dollar(nb_dollar - 1);
	*var = *var + nb_dollar;
	extend = expand(var);
	if (!extend && !*result)
	{
		free(result);
		return (NULL);
	}
	result = concat_str(result, extend);
	return (result);
}
