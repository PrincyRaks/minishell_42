/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 15:55:15 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(tokens);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(tokens);
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
					|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "env") == 0 
					|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0)
					execute_builtin(*data_cmd);
				// else
				// {
				// 	executable = find_executable((*data_cmd)->token_cmd->cmd_str);
				// 	if (executable)
				// 	{
				// 		if (fork() == 0)
				// 		{
				// 			if (execve(executable, array_tokens(*data_cmd), get_tabenv()) == -1)
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
