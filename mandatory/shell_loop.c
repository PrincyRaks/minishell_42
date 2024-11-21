/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/21 15:18:17 by rrakotos         ###   ########.fr       */
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

void	execute_builtin(t_tokens *tokens)
{
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(tokens);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(tokens);
}

void	shell_loop(void)
{
	char		*input;
	t_tokens	**data_cmd;
	char		*cmd;
	// char		*executable;

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
			// test une seule commande fotsiny ty an !
			if (data_cmd != NULL)
			{
				cmd = (*data_cmd)->token_cmd->cmd_str;
				if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
					|| ft_strcmp(cmd, "exit") == 0)
					execute_builtin(*data_cmd);
				// else
				// {
				// 	executable = find_executable((*data_cmd)->token_cmd->cmd_str);
				// 	if (executable)
				// 	{
				// 		if (fork() == 0)
				// 		{
				// 			if (execve(executable, get_tabargv(*data_cmd), get_tabenv()) == -1)
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
				// 		printf("command not found: %s\n",(*data_cmd)->token_cmd->cmd_str);
				// }
				// free_array(args);
			}
		}
		// free(input);
	}
}
