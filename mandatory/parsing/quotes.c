/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:18:50 by rrakotos          #+#    #+#             */
/*   Updated: 2024/10/30 16:49:10 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *handle_quotes(char *input)
{
    char    **cmd;
    char    *new_input;
    int     i;

    if (ft_strchr(input, '"') == NULL && ft_strchr(input, '\'') == NULL)
        return (input);
    cmd = ft_split(input, '"');
    if (!cmd)
        return (input);
    i = -1;
    new_input = ft_calloc(1, sizeof(char));
    while (cmd[++i] != NULL)
        new_input = ft_strjoin(new_input, cmd[i]);
    free_table(cmd);
    // cmd = ft_split()
    return (NULL);
}
