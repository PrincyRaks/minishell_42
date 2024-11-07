/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:59:16 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/07 12:52:52 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_tokens(char *input)
{
    char    **tab;
    int     i;

    i = -1;
    tab = ft_split(input, ' ');
    while (tab[++i] != NULL)
    {
    }
    
}

void    init_cmd(char *str){}

void    init_args(char *str){}