/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:20:44 by rrakotos          #+#    #+#             */
/*   Updated: 2024/10/21 14:20:44 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(char const *s, char c)
{
	size_t	len;

	if (!*s)
		return (0);
	len = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			len++;
		while (*s != c && *s)
			s++;
	}
	return (len);
}

char	*store_word(char const *start, char c)
{
	char	*word;
	size_t	len_w;
	size_t	i;

	len_w = 0;
	if (ft_strchr(start, c))
		len_w = ft_strchr(start, c) - start;
	else
		len_w = ft_strlen(start);
	word = (char *)malloc(sizeof(char) * (len_w + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len_w)
	{
		word[i] = ((char *)start)[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*free_word(char **str, int nb_word)
{
	while (nb_word)
	{
		free(str[nb_word]);
		nb_word--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**list_w;
	size_t	i;

	list_w = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!list_w)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			list_w[i] = store_word(s, c);
			if (!list_w[i])
				free_word(list_w, i);
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	list_w[i] = NULL;
	return (list_w);
}
