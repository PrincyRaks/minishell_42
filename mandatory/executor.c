/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/03 13:27:58 by mrazanad         ###   ########.fr       */
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

char	*find_executable(char *command)
{
	char		*full_path;
	int			i;
	char		*path_tmp;
	char		**paths;
	t_data_env	*path_exec;

	full_path = NULL;
	i = 0;
	path_tmp = NULL;
	paths = NULL;
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		// else
		// 	handle_path_command(command, 0, 0);
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
			// free_array(paths);
			// return (NULL);
			break ;
		}
		full_path = ft_strjoin(path_tmp, command);
		// free(path_tmp);
		path_tmp = NULL;
		if (!full_path)
		{
			// free_array(paths);
			// return (NULL);
			break ;
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
