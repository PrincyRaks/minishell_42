/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:25:20 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/17 08:45:49 by mrazanad         ###   ########.fr       */
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

int	search_working_directory(char *command)
{
	char			cwd[PATH_MAX];
	DIR				*dir_ptr;
	struct dirent	*read_dir;

	if (!getcwd(cwd, sizeof(cwd)))
		return (0);
	dir_ptr = opendir(cwd);
	if (!dir_ptr)
	{
		perror("opendir");
		return (0);
	}
	read_dir = readdir(dir_ptr);
	while (read_dir != NULL)
	{
		if (!ft_strcmp(read_dir->d_name, command) && !access(read_dir->d_name,
				X_OK))
		{
			closedir(dir_ptr);
			return (1);
		}
		read_dir = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (0);
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
	if (search_working_directory(command))
	{
		if (paths)
			free_array(paths);
		return (ft_strdup(command));
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
