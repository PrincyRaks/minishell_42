/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/24 10:45:39 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  check delimiter if quotes exist "" or ''
void    open_heredoc(t_flow  *flow)
{
    char    *delimiter;
    char    *input_hd;
    // int     fd;

    if ((!flow || !flow->word) && flow->operand != HEREDOC)
        return ;
    delimiter = flow->word;
    input_hd = NULL;
    // fd = open();
    while (!input_hd || ft_strcmp(delimiter, input_hd) != 0)
    {
        input_hd = readline("heredoc► ");
        if (!input_hd)
            return ;
        // handle quotes and var
        printf("%s\n", input_hd);
    }
}
