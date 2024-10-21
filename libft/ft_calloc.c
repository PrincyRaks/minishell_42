/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:24:09 by rrakotos          #+#    #+#             */
/*   Updated: 2024/08/26 14:24:22 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*memory;

	memory = malloc(elementCount * elementSize);
	if (!memory)
		return (NULL);
	ft_bzero(memory, elementCount * elementSize);
	return (memory);
}
