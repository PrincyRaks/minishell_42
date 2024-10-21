/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/21 18:34:00 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_executable(char *path)
{
    return access(path, X_OK) == 0;
}

char *find_executable(char *command, char **envp)
{
    char *path_env;
    char **paths;
    char *full_path;
    int i;

    path_env = getenv("PATH");
    if (command[0] == '/' || command[0] == '.')
    {
        if (is_executable(command))
            return (ft_strdup(command));
        else    return (NULL);
    }
    
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], '/');
        full_path = ft_strjoin(full_path, command);
        
        if (is_executable(full_path))
        {
            free_array(paths);
            return (full_path);
        }
        i++;
    }
    free_array(paths);
    return (NULL);
}