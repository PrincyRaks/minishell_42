/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/14 14:08:05 by mrazanad         ###   ########.fr       */
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

static char	*check_direct_path(char *command)
{
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(char *command, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(ft_strdup(paths[i]), "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	if (paths)
		free_array(paths);
	return (NULL);
}

char	*find_executable(char *command)
{
	t_data_env	*path_exec;
	char		**paths;
	char		*result;

	if (!command)
		return (NULL);
	result = check_direct_path(command);
	if (result)
		return (result);
	path_exec = ft_getenv("PATH");
	paths = NULL;
	if (path_exec && path_exec->value)
		paths = ft_split(path_exec->value, ':');
	return (search_in_path(command, paths));
}
