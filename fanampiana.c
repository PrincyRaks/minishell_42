
char	*find_executable(char *command)
{
	char		*full_path;
	int			i;
	// char		*path_tmp;
	char		**paths;
	t_data_env	*path_exec;

	full_path = NULL;
	i = 0;
	// path_tmp = NULL;
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
		full_path = ft_strjoin(ft_strdup(paths[i]), "/");
		// if (!path_tmp)
		// {
		// 	// free_array(paths);
		// 	// return (NULL);
		// 	break ;
		// }
		full_path = ft_strjoin(full_path, command);
		// free(path_tmp);
		// path_tmp = NULL;
		// if (!full_path)
		// {
		// 	// free_array(paths);
		// 	// return (NULL);
		// 	break ;
		// }
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		// full_path = NULL;
		i++;
	}
	if (paths)
		free_array(paths);
	return (NULL);
}


void free_array(char **array) {
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i] != NULL) 
	{
        if (array[i] != NULL)
            free(array[i]);
        i++;
    }
    free(array);
}
