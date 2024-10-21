/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:26:41 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:26:42 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		while (count-- > 0)
			d[count] = s[count];
	}
	else if (d <= s)
	{
		while (i < count)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
