/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/26 16:21:13 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void display_env(void)
{
    char    **env;

    env = get_envrange();
    while (*env != NULL)
    {        
        printf("%s\n", *env);
        env++;
    }
}

int ft_export(t_tokens *tokens)
{
	int	len_arg;

	len_arg = count_arg(tokens->token_arg);
    if(len_arg < 1)
    {
        display_env();
        return (0);
    }
    return (0);
}
