/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:07:35 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 14:09:01 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parse_redirections(char *input, t_redir **redirs)
{
    char **args;
    char **filtered_args;

    args = ft_split(input, ' ');
    filtered_args = malloc(sizeof(char *) * (ft_arraylen(args) + 1));
    if (!filtered_args)
        return (NULL);
    process_arguments(args, filtered_args, redirs);
    free_array(args);
    return (filtered_args);
}