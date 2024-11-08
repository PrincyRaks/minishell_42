/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:48 by rrakotos          #+#    #+#             */
/*   Updated: 2024/10/30 16:46:36 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_table(void **tab)
{
    int i;

    i = -1;
    while (tab[++i] != NULL)
        free(tab[i]);
    free(tab);
}