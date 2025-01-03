/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:32:06 by mrazanad          #+#    #+#             */
/*   Updated: 2024/02/27 14:32:08 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*strnew;
	unsigned int	i;
	unsigned int	j;

	strnew = (char *)malloc(len + 1);
	if (!s || !(strnew))
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
	{
		strnew[j] = s[i];
		j++;
		i++;
	}
	strnew[j] = '\0';
	return (strnew);
}
