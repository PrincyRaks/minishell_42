/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:24:50 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:24:57 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_nbr(int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*nbr_str(size_t size, int n, int is_neg)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	*(str + size) = '\0';
	while (size--)
	{
		*(str + size) = (n % 10) + '0';
		n = n / 10;
	}
	if (is_neg == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		is_neg;

	is_neg = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_nbr(n);
	if (n < 0)
	{
		n = -n;
		is_neg = 1;
		len++;
	}
	return (nbr_str(len, n, is_neg));
}
