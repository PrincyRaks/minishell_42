/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 13:54:57 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_command(char *input, char **paths, char **envp)
{
    char **args;
    t_redir *redirs;

    add_history(input);
    redirs = NULL;
    args = parse_redirections(input, &redirs);
    if (args && args[0])
    {
        if (is_builtin(args[0]))
            execute_builtin(args);
        else
            execute_command(args, paths, redirs, envp);
    }
    free_array(args);
    free_redirs(redirs);
}

void shell_loop(char **envp)
{
    char **paths;
    char *input;

    paths = get_path(envp);
    while (1)
    {
        input = readline("👾⇒ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            handle_command(input, paths, envp);
        }
        printf("\n");
        free(input);
    }
    free_array(paths);
}
