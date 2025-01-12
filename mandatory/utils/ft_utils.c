/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:24:33 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/03 17:19:42 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*concat_str(char *prev_result, char *handle)
{
	char	*str;

	if (!handle)
		handle = ft_calloc(1, sizeof(char));
	str = ft_strjoin(prev_result, handle);
	free(handle);
	return (str);
}

int	is_onlyspace(char *str)
{
	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str== '\0')
		return (1);
	return (0);
}

// char	*join_onespace(char *s1, char *s2)
// {
// 	char	*new_s;
// 	char	*tmp_s1;
// 	size_t	len;

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	if (*s1 && *s2)
// 		len++;
// 	new_s = ft_calloc((len + 1), 1);
// 	if (!new_s)
// 		return (free(s1), NULL);
// 	tmp_s1 = s1;
// 	while (*tmp_s1)
// 		*(new_s++) = *(tmp_s1++);
// 	if (*s1 && *s2)
// 		*(new_s++) = 32;
// 	while (*s2)
// 		*(new_s++) = *(s2++);
// 	free(s1);
// 	return (new_s - len);
// }
