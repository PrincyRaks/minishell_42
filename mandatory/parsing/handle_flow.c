/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:53:33 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/17 17:24:12 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator  check_operand(char *str)
{
    t_operator operand;
    char    next_char;

    operand = INPUT;
    next_char = *(str + 1);
}

static int handle_flow(t_tokens *token, char **input)
{
    if (!input && !token)
        return (0);
    while (**input != '\0' && **input != '|')
    {
        while (**input != ' ')
            (*input)++;
        if (**input != '>' && **input != '<')
            // store the file or delimiter
    }
}
