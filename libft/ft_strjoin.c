/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:28:09 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:28:11 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	while (s1[i])
	{
		new_s[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_s[i + j] = ((char *)s2)[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}
