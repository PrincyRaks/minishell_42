/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:28:56 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:29:02 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_same(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			i;
	unsigned int	start_i;

	i = 0;
	while (is_same(s1[i], set) == 1)
		i++;
	start_i = i;
	i = ft_strlen(s1);
	while (is_same(s1[i], set) == 1 || s1[i] == '\0')
		i--;
	return (ft_substr(s1, start_i, i - start_i + 1));
}
