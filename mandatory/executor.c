/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/01 21:55:01 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_only_dots(const char *command)
{
	int	i;

	if (!command || command[0] == '\0')
		return (false);
	i = 0;
    while (command[i])
    {
        if (command[i] != '.')
            return (false);
        i++;
    }
    return (true);
}


char *find_executable(char *command)
{
    char *full_path = NULL;
    int i = 0;
    char *path_tmp = NULL;
    char **paths = NULL;
    t_data_env *path_exec;

    if (is_only_dots(command))
        return (NULL);
    if (command[0] == '/' || command[0] == '.')
    {
        if (access(command, F_OK | X_OK) == 0)
            return (ft_strdup(command));
        return (NULL);
    }
    path_exec = ft_getenv("PATH");
    if (path_exec)
        paths = ft_split(path_exec->value, ':');
    while (paths && paths[i])
    {
        path_tmp = ft_strjoin(paths[i], "/");
        if (!path_tmp)
        {
            free_array(paths);
            return (NULL);
        }
        full_path = ft_strjoin(path_tmp, command);
        free(path_tmp);

        if (!full_path)
        {
            free_array(paths);
            return (NULL);
        }
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free_array(paths);
            return (full_path);
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    if (paths)
        free_array(paths);
    return (NULL);
}


