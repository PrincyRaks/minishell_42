/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/22 17:12:30 by rrakotos         ###   ########.fr       */
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

void	shell_loop(char **envp)
{
	char	*input;
	char	**args;
	char	**paths;
	char	*executable;

	paths = get_path(envp);
	while (1)
	{
		input = readline(" 🚀> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			args = ft_split(input, ' ');
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
			}
			else
				printf("%s: command not found\n", args[0]);
			free_array(args);
			free(executable);
		}
		// free(input);
	}
	free_array(paths);
}
