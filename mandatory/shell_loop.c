/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/11 13:35:40 by rrakotos         ###   ########.fr       */
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

void shell_loop(char **envp)
{
    char *input;
    char **args;
    char **paths;
    char *executable;

    paths = get_path(envp);
    while (1)
    {
        input = readline("👾⇒ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            add_history(input);
            args = ft_split(input, ' ');
            if (ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "exit") == 0)
            {
                execute_builtin(args);
            }
            else
            {
                executable = find_executable(args[0], paths);
                if (executable)
                {
                    if (fork() == 0)
                    {
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
            free_array(args);
        }
        free(input);
    }
    free_array(paths);
}
