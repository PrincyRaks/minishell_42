/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/22 08:58:11 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "minishell.h"

char **get_path(char **envp)
{
    int i = 0;
    char *path_value = NULL;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_value = envp[i] + 5;
            break;
        }
        i++;
    }
    if (path_value)
        return ft_split(path_value, ':');

    return NULL;
}

char *find_executable(char *command, char **paths)
{
    char *full_path;
    int i = 0;

    if (command[0] == '/' || command[0] == '.')
    {
        if (access(command, X_OK) == 0)
            return ft_strdup(command);
        else
            return NULL;
    }

    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, command);

        if (access(full_path, X_OK) == 0)
            return full_path;

        free(full_path);
        i++;
    }
    return NULL;
}

