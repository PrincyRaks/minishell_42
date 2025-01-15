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
	char	*tmp_s1;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = ft_calloc((len + 1), sizeof(char));
	if (!new_s)
	{
		free((char *)s1);
		return (NULL);
	}
	tmp_s1 = (char *)s1;
	while (*tmp_s1)
		*(new_s++) = *(tmp_s1++);
	while (*s2)
		*(new_s++) = *(s2++);
	free((char *)s1);
	return (new_s - len);
}
