/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/24 16:26:34 by mrazanad         ###   ########.fr       */
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
    char *full_path;
    int i;
    char *path_tmp;
    char **paths;
    t_data_env *path_exec;

    if (is_only_dots(command))
    {
        ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
        return (NULL);
    }
    if (command[0] == '/' || command[0] == '.')
    {
        if (access(command, F_OK) != 0)
        {
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
            return (NULL);
        }
        if (access(command, X_OK) != 0)
        {
            ft_putstr_fd(command, 2);
			ft_putstr_fd(": Permission denied \n", 2);
            return (NULL);
        }
        return (ft_strdup(command));
    }
    paths = NULL;
    path_exec = ft_getenv("PATH");
    if (path_exec != NULL)
        paths = ft_split(path_exec->value, ':');
    i = 0;
    while (paths && paths[i])
    {
        path_tmp = ft_strdup(paths[i]);
        full_path = ft_strjoin(path_tmp, "/");
        full_path = ft_strjoin(full_path, command);
        if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
        {
            free_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    if (paths)
        free_array(paths);
    // write(STDERR_FILENO, command, ft_strlen(command));
    // write(STDERR_FILENO, "eto ngamba: command not found\n", 20);
    return (NULL);
}

