/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:53:46 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 13:55:03 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
void execute_builtin(char **args)
{
    if (ft_strcmp(args[0], "cd") == 0)
        ft_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
}

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || 
            ft_strcmp(cmd, "pwd") == 0 || 
            ft_strcmp(cmd, "exit") == 0);
}

void execute_command(char **args, char **paths, t_redir *redirs, char **envp)
{
    char *executable;

    executable = find_executable(args[0], paths);
    if (executable)
    {
        if (fork() == 0)
        {
            if (apply_redirection(redirs) == -1)
                exit(EXIT_FAILURE);
            if (execve(executable, args, envp) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
            wait(NULL);
        free(executable);
    }
    else
        printf("command not found: %s\n", args[0]);
}