/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/20 12:42:02 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	execute_builtin(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
}

void	shell_loop()
{
	char		*input;
	t_tokens	**data_cmd;
	// char	**args;
	// char	*executable;

	while (1)
	{
		input = readline("👾⇒ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			data_cmd = store_token(input);
			// if (ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "pwd") == 0
			// 	|| ft_strcmp(args[0], "exit") == 0)
			// 	execute_builtin(args);
			// else
			// {
			// 	executable = find_executable(args[0]);
			// 	if (executable)
			// 	{
			// 		if (fork() == 0)
			// 		{
			// 			if (execve(executable, args, get_tabenv()) == -1)
			// 			{
			// 				perror("execve");
			// 				exit(EXIT_FAILURE);
			// 			}
			// 		}
			// 		else
			// 			wait(NULL);
			// 		free(executable);
			// 	}
			// 	else
			// 		printf("command not found: %s\n", args[0]);
			// }
			// free_array(args);
		}
		// free(input);
	}
}
