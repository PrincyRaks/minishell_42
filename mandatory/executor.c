/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/16 12:07:51 by mrazanad         ###   ########.fr       */
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

	i = 0;

	if (is_only_dots(command))
	{
		printf("command not found: %s\n", command);
		return (NULL);
	}
	
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
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

