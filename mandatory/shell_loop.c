/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/22 09:05:07 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void shell_loop(char **envp)
{
    char *input;
    char **args;
    char **paths = get_path(envp);
    char *executable;

    while (1)
    {
        input = readline(" 👽 > ");
        
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
        {
            add_history(input);
            args = ft_split(input, ' ');
            executable = find_executable(args[0], paths);

            if (executable)
            {
                if (fork() == 0)
                {
                    execve(executable, args, envp);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
                else
                    wait(NULL);
            }
            else
                printf("%s: command not found\n", args[0]);
            free_array(args);
            free(executable);
        }

        free(input);
    }

    free_array(paths);
}


