/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/12 16:20:34 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gerer "" '' . .. (is_directory)
char	*find_executable(char *command)
{
	char		*full_path;
	int			i;
	char		*path_tmp;
	char		**paths;
	t_data_env	*path_exec;

	i = 0;
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	paths = NULL;
	path_exec = ft_getenv("PATH");
	if (path_exec != NULL)
		paths = ft_split(path_exec->value, ':');
	while (paths && paths[i])
	{
		path_tmp = ft_strdup(paths[i]);
		full_path = ft_strjoin(path_tmp, "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}
