/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:25:37 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/03 11:08:28 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *parse_redirections(char *input, t_arg **args)
{
    t_arg *current = *args;

    while (input && *input != '\0') {
        if (*input == '>') {
            if (*(input + 1)) {
                current->errnum = O_WRONLY | O_CREAT | O_APPEND;
                input++;
            } else {
                current->errnum = SYNTAX_ERROR;
                return (NULL);
            }
        }
        else if (*input == '<') {
            if (*(input + 1)) {
                current->errnum = O_RDONLY;
                input++;
            } else {
                current->errnum = SYNTAX_ERROR;
                return (NULL);
            }
        }
        input++;
    }
    return (input);
}



