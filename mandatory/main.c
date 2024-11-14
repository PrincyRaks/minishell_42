/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:31:19 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 10:45:33 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    dup_env(envp);
    // ft_env();
    // printf("%s\n", getenv("HOME"));
    // printf("key: %s et value: %s\n", (*get_data_env())->key, (*get_data_env())->value);
    // char *s = "$HOME";
    // if (ft_getenv(s) != NULL)
        // printf("key: %s et value: %s\n", ft_getenv(s)->key, ft_getenv(s)->value);
    shell_loop(envp);
    return (0);
}
