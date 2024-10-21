/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:28:14 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:28:16 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= size)
		return (len_src + size);
	while (i < ((size - len_dst) - 1) && ((char *)src)[i])
	{
		dst[len_dst + i] = ((char *)src)[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
